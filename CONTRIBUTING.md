# Contributing to arm-cortex-m0-core

Thank you for your interest in contributing! This repository is a header-only, CMSIS-like C++20 library for accessing
ARM Cortex-M0 core peripherals. The surface is small, so the contribution flow is light, but a few conventions keep the
library consistent and safe to depend on.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How to Contribute](#how-to-contribute)
    - [Reporting Bugs](#reporting-bugs)
    - [Suggesting Features](#suggesting-features)
    - [Pull Requests](#pull-requests)
- [Development Setup](#development-setup)
- [Testing Your Change](#testing-your-change)
- [Coding Standards](#coding-standards)
- [Commit Messages](#commit-messages)
- [Documentation](#documentation)
- [Releasing](#releasing)

---

## Code of Conduct

This project adheres to the Contributor Covenant Code of Conduct. By participating, you are expected to uphold this code.
Please see [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for details.

---

## How to Contribute

### Reporting Bugs

Before submitting a bug report:

1. Check the [existing issues](https://github.com/embedded-society/arm-cortex-m0-core/issues) to avoid duplicates.
2. Make sure you're using the latest version of the library from `main`.
3. Gather the details the **bug report** issue template asks for — the header and API involved, the toolchain and
   version, target device, a minimal reproducing snippet, and the observed vs expected behaviour.

When submitting, use the **bug report** issue template; it lists every field to fill in so nothing is missed.

### Suggesting Features

We welcome suggestions for additional peripherals, registers, or accessor helpers that fit the Cortex-M0 core. Before submitting:

1. Check [existing issues](https://github.com/embedded-society/arm-cortex-m0-core/issues) for similar ideas.
2. Consider whether the addition belongs to the **Cortex-M0 core** specifically (this library's scope) or to a
   device-specific peripheral (which belongs in a device support package, not here).

When submitting, use the **feature request** issue template.

### Pull Requests

#### Before You Start

1. For non-trivial changes, open an issue first to discuss the approach.
2. Fork the repository.
3. Create a feature branch from `main` with a descriptive name (kebab-case), e.g.
   `add-mpu-registers`, `fix-systick-reload-mask`, `document-nvic-priorities`.
4. Make your changes following the [coding standards](#coding-standards).

#### PR Requirements

- [ ] The library still builds and **all tests pass** in the
      [`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests) superproject for the
      `M0` target (see [Testing Your Change](#testing-your-change))
- [ ] If the change alters the API or register layout, a companion PR to
      [`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests) updates or adds tests,
      and is linked from this PR
- [ ] Headers are formatted with `clang-format` (`.clang-format`) — run `clang-format -i include/arm-cortex-m0-core/*.hpp`
- [ ] No trailing whitespace, final newline present (`.editorconfig` will guide you)
- [ ] British spelling used in comments and documentation
- [ ] Style matches [STYLE.md](STYLE.md)
- [ ] [CHANGELOG.md](CHANGELOG.md) is **not** touched in feature PRs — it is updated only when a release is cut (see [Releasing](#releasing))

#### PR Process

1. Submit your PR against the `main` branch.
2. Fill out the PR template completely, linking any companion tests PR.
3. CODEOWNERS reviewers are requested automatically; address any feedback.
4. Once approved, a maintainer will merge.

---

## Development Setup

### Prerequisites

- **A C++20 cross-compiler** targeting `arm-none-eabi` — the [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain)
  (`arm-none-eabi-gcc`) or the [LLVM Embedded Toolchain for Arm](https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm).
- **CMake** and a build generator such as Ninja — only needed to build the tests (see below), not the library itself.
- **`clang-format`** for formatting the headers.
- A Git client.

### Clone

```bash
git clone git@github.com:embedded-society/arm-cortex-m0-core.git
cd arm-cortex-m0-core
```

The library is header-only: there is nothing to compile in this repo directly. It is consumed via
`add_subdirectory()` (an `INTERFACE` CMake target) and exercised by the tests superproject.

---

## Testing Your Change

The C++ in this repo is not compiled here — it is built and exercised by the
[`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests) superproject, which pulls
this library in as a submodule. **Any change to this library must keep that test suite green for the `M0` target.**

1. Check out the tests superproject with submodules, pointing this library's submodule at your branch:

    ```bash
    git clone --recurse-submodules git@github.com:embedded-society/arm-cortex-mx-core-tests.git
    cd arm-cortex-mx-core-tests
    # point the arm-cortex-m0-core submodule at your feature branch/commit
    ```

2. Configure and build the tests for the Cortex-M0 target and run them (see that repo's own README/CONTRIBUTING for
   the exact preset and runner — that is the single source of truth for how the tests are driven):

    ```bash
    cmake -B build -DARM_CORTEX_M_ARCH=M0
    cmake --build build
    ```

3. Confirm the suite passes. If your change alters the public API or a register layout, **add or update tests in the
   superproject** and open a **companion PR** there, linked from your PR here. A change that would break the tests must
   not merge before its companion tests PR is ready.

Machine-checked C++ analysis (clang-tidy) also lives in the tests superproject, where a compilation database exists —
this repo ships only `.clang-format` (which needs no build). Run `clang-format` locally before pushing.

---

## Coding Standards

C++ style, CMake style, Markdown / YAML / JSON / JavaScript style, and English style are all defined in
**[STYLE.md](STYLE.md)** — it is the single source of truth for every convention in this repo. C++ formatting is
additionally machine-enforced by [`.clang-format`](.clang-format). Read STYLE.md before your first contribution; this
guide does not restate its rules, so that they can never drift out of sync.

---

## Commit Messages

Imperative-mood subject line, capitalised first word, no trailing period, under 72 characters. Examples from this repo's history:

```text
Update copyright year to 2026
Add Dependabot config for GitHub Actions
Set the Cortex-M0 architecture flags on the interface target
```

If the change needs more than the subject line, leave a blank line and add a body that explains the **why**, not the **what**
— the diff already shows the what. Reference issues in the footer (`Fixes #123`).

---

## Documentation

This table is the **canonical file-purpose registry** for the repository: every documentation file owns exactly one kind of
content, and that content lives only there. When you add information, put it in the file that owns it and link from elsewhere —
never copy it. If two files would say the same thing, one of them is wrong.

| File | Owns (and nothing else) |
|------|-------------------------|
| `README.md` | Project intro, and usage / library-contents documentation |
| `CONTRIBUTING.md` | This file — contribution flow, dev setup, testing procedure, and this registry |
| `STYLE.md` | Every style and convention rule (C++, CMake, Markdown, YAML, JSON, JavaScript, English) — how prose and code should look |
| `.clang-format` | The machine-enforced C++ formatting rules |
| `SECURITY.md` | Threat model, supply-chain integrity, and vulnerability reporting |
| `CODE_OF_CONDUCT.md` | Community code of conduct (verbatim Contributor Covenant 3.0 — do not edit) |
| `CHANGELOG.md` | Release history — one entry per released version, updated only when a release is cut (see [Releasing](#releasing)) |
| `.github/PULL_REQUEST_TEMPLATE.md` | The PR checklist form (links to the rules above; states none of them) |
| `.github/ISSUE_TEMPLATE/bug_report.md` | The bug-report form |
| `.github/ISSUE_TEMPLATE/feature_request.md` | The feature-request form |

STYLE.md § Single Source of Truth maps each *kind of information* to its canonical file; this table maps each *file* to the
information it owns. The two are the same principle from opposite directions — keep them consistent.

When you change the public API, update `README.md` § Contents in the same PR.

---

## Releasing

Releases are cut **only by an organisation admin** — a deliberate supply-chain control so that a single compromised
contributor account cannot ship a malicious version. The tag ruleset enforces this; see
[SECURITY.md § Release integrity](SECURITY.md#release-integrity) for how. The single source of truth for a release is
its **Git tag** — there is no version field to keep in sync (`package.json` is private local lint tooling and is not the
project version). The [`.github/workflows/release.yml`](.github/workflows/release.yml) workflow does the rest automatically.

The process:

1. On `main`, add a new section to [CHANGELOG.md](CHANGELOG.md) for the version being released, following the
   [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) format. Use a `## [x.y.z] - YYYY-MM-DD` heading and a
   matching `[x.y.z]: …/releases/tag/vx.y.z` link reference at the bottom. Merge this through a normal PR.

2. Tag the release commit and push the tag. The tag **must** be exactly `vMAJOR.MINOR.PATCH`, matching
   [Semantic Versioning](https://semver.org/spec/v2.0.0.html). Pre-release tags (e.g. `-rc1`) are not supported —
   only clean version tags trigger a release:

    ```bash
    git checkout main && git pull
    git tag v1.0.0
    git push origin v1.0.0
    ```

3. Pushing the tag triggers the release workflow, which:
    - validates the tag format,
    - extracts the notes for that version from `CHANGELOG.md` (falling back to a bare `Release x.y.z` if no section
      is found — so step 1 matters),
    - assembles a curated `arm-cortex-m0-core-vX.Y.Z.zip` bundle (the `include/` headers, `CMakeLists.txt`,
      `CHANGELOG.md`, `LICENCE`, and a bundle-specific `README.md` generated from `.github/release-assets/README.md`),
    - signs a build-provenance attestation for the bundle (see
      [SECURITY.md § Release integrity](SECURITY.md#release-integrity)),
    - creates the GitHub release, marks it "latest", and attaches the bundle as a release asset.

The bundle is a convenience so consumers can `add_subdirectory()` the library from a single archive. They may equally
use the library at the tagged commit directly, via `git` or GitHub's auto-generated source archives.

To undo a mistaken release, delete both the GitHub release and the tag (`git push origin :refs/tags/vX.Y.Z`), fix the
issue, and re-tag.

---

## Questions?

- Open a [Discussion](https://github.com/embedded-society/arm-cortex-m0-core/discussions) for questions.
- Check existing issues and discussions first.
- Be patient — maintainers are volunteers.

Thank you for contributing!
