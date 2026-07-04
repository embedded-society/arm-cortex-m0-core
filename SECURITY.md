# Security Policy

## Supported Versions

| Version | Supported          |
|---------|--------------------|
| 0.x.x   | Yes (development)  |

Once we reach v1.0, we will maintain security updates for the current major version and one previous major version.

## Threat Model

This repository is a header-only C++ library that is compiled directly into a consumer's firmware. It:

- Defines `volatile` register structs and pointer constants at fixed peripheral base addresses.
- Provides thin `inline` accessor functions and bit-manipulation helpers.
- Runs with full privilege on the target — there is no sandbox between this code and the hardware.

A vulnerability in this context typically means one of:

1. A register definition or accessor that is **wrong in a way that silently corrupts hardware state** — an incorrect
   base address, a bad struct offset/reserved gap, or a wrong bit position — causing the consumer's firmware to write
   the wrong peripheral register.
2. Undefined behaviour in an accessor (e.g. an out-of-range shift, signed-overflow, or aliasing bug) that a compiler
   may exploit to miscompile the caller.
3. Malicious code hidden in a header — anything that does more than compute a memory-mapped access, e.g. an
   `asm` block or `reinterpret_cast` that reaches outside the intended peripheral.

Because the library compiles straight into firmware that often runs in safety-critical or secure contexts, correctness
*is* security here. If you believe you've found something matching one of those, please report it privately as described below.

### Supply-chain integrity

The threats above describe what a *consumer* risks by using this library. The other half of the model is protecting the
repository *itself* from tampering. Because the repo is deliberately tiny — a handful of headers plus governance docs and
a thin CI setup — every part of it is small enough to review in full, and anything unexpected should stand out immediately.
The concrete risks:

1. **Malicious CI/CD changes.** A pull request that alters a workflow to exfiltrate secrets, escalate `permissions:`,
   pull in an unpinned or unfamiliar third-party action, or make the `github-script` cache-cleanup step do more than
   prune caches. CI runs with a token and (for some jobs) write scope, so this is the highest-value target in the repo.
2. **Unexpected files.** Any new file that isn't a header, a governance/Markdown document, `CMakeLists.txt`, or part of
   the known CI/lint tooling. Binaries, build artifacts, scripts, `curl | sh`-style installers, or vendored dependencies
   have no reason to appear here and should be treated as suspicious until explained.
3. **Fishy header content.** A subtly wrong register address or bit position, a new `asm` block or `reinterpret_cast`
   that reaches beyond the intended peripheral, an `#include` of something outside the freestanding standard library, or
   any code path that does more than a memory-mapped access. Changes to register maps deserve datasheet-level scrutiny.

### What reviewers watch for

These invariants already hold in `main`; a change that weakens any of them is a red flag, not a routine diff:

- **Actions are pinned to full commit SHAs** (with a `# vX.Y.Z` comment), never to a mutable tag or branch.
- **Workflows use least-privilege `permissions:`** — read-only by default; write scope only where a job genuinely
  needs it (e.g. `actions: write` for cache cleanup) and never broader.
- **PR workflows restore caches but never save them**, so a fork PR cannot poison the shared cache.
- **Dependencies are pinned** in `package-lock.json` and installed with `npm ci`; version bumps arrive as reviewable
  Dependabot PRs, not as ad-hoc edits to the lockfile.
- **No new file appears without a clear reason** tied to the PR's stated purpose.
- **Headers stay freestanding and in scope** — only `volatile` register access, bit helpers, and inline accessors; no
  hosted-standard-library includes, no network or filesystem access, no `asm`/`reinterpret_cast` reaching beyond the
  documented peripheral. Register-map changes are checked against the ARM datasheet.
- **The tests stay green.** Every change keeps the [`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests)
  suite passing for the `M0` target — a wrong register definition should fail a test, not reach a release.

If you spot a merged change that violates one of these — or a PR that tries to — please report it privately as below,
even if you're not certain it's exploitable.

### Release integrity

Cutting a release is intentionally restricted, so a compromised contributor account cannot ship a malicious version:

- **Only an organisation admin can create a release.** A tag ruleset restricts creation, update, and deletion of all
  tags, with organisation admins as the sole bypass actor. Because the release workflow triggers on a pushed
  `vMAJOR.MINOR.PATCH` tag, nobody without that privilege can start a release — and the workflow's `GITHUB_TOKEN`
  cannot create the tag to trigger itself.
- **Release tags must point at a signed commit** (`required_signatures` on the same ruleset) and are immutable —
  they cannot be force-updated or deleted to retarget a published version.
- **The release asset is a plain copy of tracked files, not a compiled build.** Each release attaches a
  `arm-cortex-m0-core-vX.Y.Z.zip` bundle containing the `include/` headers, `CMakeLists.txt`, `CHANGELOG.md`, `LICENCE`,
  and a bundle-specific `README.md` — all copied verbatim from the signed, tagged commit by the same admin-gated
  workflow. There is no compilation step and nothing executable is generated, so the archive introduces no attack
  surface beyond the tagged source itself; consumers who prefer can ignore it and use the library at the tag directly.
- **The bundle carries a signed build-provenance attestation.** The release workflow signs a
  [build provenance](https://docs.github.com/actions/security-guides/using-artifact-attestations) statement binding
  the archive's digest to the exact workflow run and commit that produced it. This is a verifiable proof of origin,
  not just the argument above — anyone can check it with:

    ```bash
    gh attestation verify arm-cortex-m0-core-vX.Y.Z.zip --repo embedded-society/arm-cortex-m0-core
    ```

  A tampered or re-hosted archive fails this check.

See [CONTRIBUTING.md § Releasing](CONTRIBUTING.md#releasing) for the release procedure.

## Reporting a Vulnerability

**Please do NOT report security vulnerabilities through public GitHub issues.**

### How to Report

1. **Preferred:** use [GitHub Security Advisories](https://github.com/embedded-society/arm-cortex-m0-core/security/advisories/new) to report the vulnerability privately.

2. **Alternative:** email the maintainer directly at <matejg03@gmail.com>.

### What to Include

When reporting, please include:

- A clear description of the vulnerability and the conditions that trigger it.
- Steps to reproduce — including the exact library version, compiler and version, target device, and a minimal snippet.
- Potential impact assessment.
- Any suggested fix or mitigation (optional but appreciated).

### Response Timeline

| Action | Timeframe |
|--------|-----------|
| Initial acknowledgement | Within 48 hours |
| Preliminary assessment | Within 1 week |
| Fix development | Depends on severity and complexity |
| Security advisory publication | After fix is available |

### What to Expect

1. **Acknowledgement.** We will acknowledge receipt of your report within 48 hours.

2. **Communication.** We will keep you informed of our progress and may ask for additional information.

3. **Credit.** Unless you prefer to remain anonymous, we will credit you in the security advisory and release notes.

4. **Disclosure.** We follow responsible disclosure practices. We ask that you give us reasonable time to address the issue before any public disclosure.

---

*This security policy was last updated on 2026-07-04.*
