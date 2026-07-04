# Style Guide

Style conventions for `arm-cortex-m0-core`. Covers C++ (the primary content of this repo), CMake, Markdown, YAML, JSON, JavaScript, and English.

---

## Table of Contents

- [General Rules](#general-rules)
- [Single Source of Truth](#single-source-of-truth)
- [C++](#c)
- [CMake](#cmake)
- [Markdown](#markdown)
- [YAML](#yaml)
- [JSON](#json)
- [JavaScript](#javascript)
- [British English 🇬🇧](#british-english-)
- [Tooling](#tooling)

---

## General Rules

| Rule | Setting |
|------|---------|
| Indentation | 4 spaces (no tabs) |
| Charset | UTF-8 |
| Final newline | Always |
| Trailing whitespace | Trim (except Markdown, where it's significant for line breaks) |
| Line endings | LF in repo (`.gitattributes` normalises on checkout) |

These rules are enforced by `.editorconfig`. Install the EditorConfig plugin for your editor:

- **VS Code:** [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig)

There is no hard column limit, but aim to keep lines comfortably below ~120 characters where it doesn't hurt readability.

**Do not column-align trailing comments.** Use a single space before the comment marker (`//`, `//!<`, `#`), regardless of language. Padding to line up
comments across rows churns the diff whenever the longest line changes and drifts out of alignment over time.

---

## Single Source of Truth

Avoid duplicating information across files. Each piece of information has one canonical location; everywhere else links to it
rather than restating it. This table maps each *kind of information* to the file that owns it. For the reciprocal view — each
*file* and the single kind of content it owns — see [CONTRIBUTING.md § Documentation](CONTRIBUTING.md#documentation), the
canonical file-purpose registry. Keep the two consistent.

| Information | Canonical Source |
|-------------|------------------|
| Project intro and overview | `README.md` (intro) |
| Usage and library contents | `README.md` § Usage / § Contents |
| Contribution flow, dev setup, testing procedure | `CONTRIBUTING.md` |
| File-purpose registry (which file owns what) | `CONTRIBUTING.md` § Documentation |
| Style and convention rules (all languages + English) | `STYLE.md` (this file) |
| C++ formatting rules (machine-enforced) | `.clang-format` |
| Formatting rules (indent, EOL, charset) | `.editorconfig` |
| Markdown lint rules | `.markdownlint.json`, `.markdownlint-cli2.jsonc` |
| Local task shortcuts | `Taskfile.yml` |
| Pinned lint tooling versions | `package.json`, `package-lock.json` |
| Threat model and security policy | `SECURITY.md` |
| Code of Conduct | `CODE_OF_CONDUCT.md` |
| Release history | `CHANGELOG.md` (will be populated at v1.0.0) |

Reference the canonical source from elsewhere; don't restate it. When updating information, update the canonical source first.

---

## C++

The header library under `include/arm-cortex-m0-core/` is the primary content of this repo. It is a header-only,
CMSIS-like C++20 library for accessing ARM Cortex-M0 core peripherals.

### Language Standard

C++20. The library is header-only and `INTERFACE`-linked; it must compile cleanly for the `arm-none-eabi` bare-metal
target with no hosted standard-library assumptions. Include only freestanding headers (`<cstdint>`, `<cstddef>`, …) —
never `<iostream>`, `<vector>`, exceptions, or RTTI.

### Formatting

Formatting is enforced by [`.clang-format`](.clang-format) (LLVM-based). Run `clang-format -i` on any header you touch;
CI in the [`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests) superproject checks it.
Key rules the config encodes:

- 4-space indentation; no tabs; 170-column limit.
- **Allman braces for functions**; **attached braces for structs, enums, and namespaces** (`struct Registers {` on one line).
- Namespace bodies are indented (`NamespaceIndentation: All`).
- Left-aligned pointers (`Type* ptr`), braced-list style (`uint32_t{1}`), no column-alignment of consecutive declarations or trailing comments.
- `template<...>` on its own line above the entity it templates; no space after `template`.
- One statement per line; `#pragma once` at the top of every header (after the licence block), not include guards.

```cpp
struct Registers {
    volatile uint32_t ISER; //!< Interrupt set-enable register (W1S).
    volatile uint32_t ICER; //!< Interrupt clear-enable register (W1C).
};
```

### Naming Conventions

| Item | Convention | Example |
|------|------------|---------|
| Namespaces | PascalCase | `ArmCortex`, `ArmCortex::Nvic` |
| Types / structs | PascalCase | `Registers` |
| Functions | camelCase | `enableIrq`, `isBitSet` |
| Constants (`constexpr`) | SCREAMING_SNAKE_CASE | `BASE_ADDRESS` |
| Register-block members | SCREAMING_SNAKE_CASE (match the datasheet) | `ISER`, `ICPR` |
| Local variables / parameters | snake_case | `irq_number` |

Peripheral register names mirror the ARM/CMSIS datasheet spelling exactly (`ISER`, `ICPR`, `CTRL`) even though that
is not British English — hardware register names are upstream identifiers, not prose.

### Namespaces

All public API lives under the `ArmCortex` namespace, with each peripheral in its own nested namespace
(`ArmCortex::Nvic`, `ArmCortex::Systick`). Do not put anything at global scope.

### Peripheral Access

Memory-mapped peripherals are exposed as a `volatile` register struct plus an `inline` pointer constant at the base
address. Keep the pattern consistent across headers:

```cpp
namespace ArmCortex::Nvic {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E100u;

    struct Registers {
        volatile uint32_t ISER; //!< Interrupt set-enable register (W1S).
    };
}

namespace ArmCortex {
    inline volatile Nvic::Registers* const NVIC = reinterpret_cast<volatile Nvic::Registers*>(Nvic::BASE_ADDRESS);
}
```

- Register members are `volatile` and use fixed-width types (`uint32_t`, `uint8_t`).
- Reserved gaps are explicit `RESERVED` array members so the struct layout matches the hardware map exactly.
- Base addresses are `inline constexpr uintptr_t` in SCREAMING_SNAKE_CASE.

### Accessor Functions

Thin accessors are `[[gnu::always_inline]] static inline`, take fixed-width parameters, and use brace-initialised
literals for shifts to avoid signed-int surprises:

```cpp
//! Enable an interrupt. ISER is W1S (write-1-to-set).
[[gnu::always_inline]] static inline void enableIrq(uint8_t irq_number)
{
    NVIC->ISER = uint32_t{1} << irq_number;
}
```

Prefer the shared helpers in `bit_utils.hpp` (`isBitSet`, `setBit`, `clearBit`) over open-coding bit twiddling.

### Type Explicitness

Use fixed-width integer types from `<cstdint>` for anything touching hardware. Avoid `auto` where a concrete type is
spellable — the reader should never have to guess a register or index type.

### Comments

Use Doxygen `//!` for a single-line brief and `//!<` for an inline member/enumerator description. One space before the
marker; never pad to align across rows.

```cpp
volatile uint32_t ISER; //!< Interrupt set-enable register (W1S).
```

The licence header at the top of every `.hpp` file uses the Apache 2.0 boilerplate in a `/* */` block:

```cpp
/*
    Copyright (C) 2026 The Embedded Society <https://github.com/embedded-society/arm-cortex-m0-core>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
```

The licence header text itself is American English (`License`) — that is the registered name of the Apache 2.0 licence. Do not anglicise it.

### Include Order

After the licence block and `#pragma once`, include same-module headers first (quoted, relative `"./x.hpp"`), then
standard library headers (angle-bracketed):

```cpp
#pragma once

#include "./bit_utils.hpp"
#include <cstdint>
```

---

## CMake

The repo's `CMakeLists.txt` defines the `INTERFACE` library target. It follows modern-CMake conventions.

- 4-space indentation; lowercase command names (`add_library`, `target_compile_features`, …). Uppercase forms
  (`ADD_LIBRARY`) are deprecated — never use them.
- `endif()` / `endforeach()` take empty parentheses.
- The library is `INTERFACE` (header-only): expose headers via `target_include_directories(... INTERFACE ...)` and
  the C++ standard via `target_compile_features(... INTERFACE cxx_std_20)`.
- Keep the Apache 2.0 licence header (hash-prefixed `#` lines) at the top of `CMakeLists.txt`.

---

## Markdown

### Headings

Use ATX-style headings with blank lines before and after:

```markdown
## Section Title

Content here.
```

### Lists

Use `-` for unordered lists and `1.` for ordered lists. Indent nested items by 4 spaces (matching the project-wide indentation).

### Code Blocks

Always specify the language (or `text` for plain text):

````markdown
```cpp
ArmCortex::Nvic::enableIrq(5);
```
````

### Trailing Whitespace

Markdown files are exempt from trailing-whitespace trimming — two trailing spaces are sometimes used as line breaks (`<br>` equivalent).

### Links

Prefer reference-style links only when a URL is reused in many places. Inline links are fine in most cases.
Use angle brackets for bare URLs (`<https://example.com>`) so they render correctly.

### Linting

Markdown is the one file type in this repo with an automated linter. Rules live in `.markdownlint.json`; the file
globs and ignores live in `.markdownlint-cli2.jsonc` — so a bare invocation lints the whole repo and stays in sync with CI.

```bash
npm ci # install the pinned markdownlint-cli2 (once)
npm run lint # lint every Markdown file — fails on any violation
npm run lint:fix # auto-fix the fixable violations in place
```

`Taskfile.yml` wraps the same npm scripts (`task lint`, `task fix`) for anyone who prefers [Task](https://taskfile.dev).
Both routes call the identical tooling, so local runs and CI never disagree. See [Tooling](#tooling) for the full picture.

---

## YAML

**Indentation.** 4 spaces for structure levels — aligned with the project-wide convention.

**List item continuation.** The keys of a list item continue 2 spaces after the dash — aligned with the first
character following the dash-and-space (standard YAML behaviour, not negotiable). Deeper nesting adds a further 2 spaces per level:

```yaml
updates:
    - package-ecosystem: "github-actions"
      directory: "/"
      schedule:
        interval: "weekly"
        day: "saturday"
        time: "00:00"
        timezone: "UTC"
```

**Column breakdown:**

| Element | Column | Explanation |
|---------|--------|-------------|
| `-` | 4 | Parent indent (4 spaces from `updates:`) |
| `package-ecosystem:`, `directory:`, `schedule:` | 6 | 2 spaces after the dash-and-space |
| `interval:`, `day:`, `time:`, `timezone:` | 8 | 2 spaces from `schedule:` (nested map) |

**Quoting.** Quote strings that look like booleans, numbers, dates, or have special characters: `"yes"`, `"00:00"`, `"weekly"`. Bare strings are fine for unambiguous identifiers.

---

## JSON

**4-space indentation.** Trailing commas are not allowed in JSON. End every file with a final newline.

```json
{
    "key": "value",
    "nested": {
        "item": 123
    }
}
```

---

## JavaScript

### Scope

JavaScript appears only in CI helper scripts under `.github/scripts/` (e.g. `cleanup-caches.js`), invoked from
workflows via `actions/github-script`. There is no application JavaScript in this repo, and no bundler or transpiler —
scripts run on the Node.js version provided by the GitHub Actions runner. Keep them dependency-free and self-contained.

### Formatting

| Setting | Value |
|---------|-------|
| Indentation | 4 spaces (no tabs) |
| String quotes | Double quotes |
| Statement terminators | Always use semicolons |
| Final newline | Always |

### Conventions

- Export the entry point as `module.exports = async ({ github, context, core }) => { ... }` — the signature
  `actions/github-script` provides. Use `core.info` / `core.warning` / `core.error` / `core.setFailed` for output,
  not `console.log`.
- Naming: `camelCase` for functions and variables, `SCREAMING_SNAKE_CASE` for constants, `PascalCase` for classes.
- Prefer `const`; use `let` only when reassignment is genuinely needed. Never use `var`.
- Give each script a top-of-file block comment (`/** ... */`) describing what it does and any environment
  variables it reads (e.g. `INPUT_DRY_RUN`).
- British spelling in comments and log strings 🇬🇧; identifiers from the GitHub API keep their upstream spelling
  (`last_accessed_at`, `size_in_bytes`, etc.).

There is no JavaScript linter or formatter wired up; match the style of the existing scripts by hand.

---

## British English 🇬🇧

Use **British English** in all prose, documentation, comments, commit messages, and PR descriptions:

| American | British |
|----------|---------|
| color | colour |
| behavior | behaviour |
| organize | organise |
| organization | organisation |
| recognize | recognise |
| characterize | characterise |
| minimize | minimise |
| optimize | optimise |
| center | centre |
| license (noun) | licence |
| defense | defence |
| analyze | analyse |
| catalog | catalogue |

**Hard exception — never anglicise:**

1. **Legal documents.** The Apache 2.0 licence header text says "License" because that is the legal text.
   Same applies to any licence file, terms of service, etc. — leave them exactly as published.
2. **Proper nouns.** "Apache License", "Organization for Ethical Source", "World Health Organization", etc. are registered names; keep them as-is.
3. **Code identifiers and hardware/library APIs.** Any identifier defined upstream — ARM/CMSIS register names like
   `ISER`, C++ standard identifiers, GitHub Actions inputs, etc. — keeps its original spelling.

When in doubt: prose is British, identifiers and legal text are exact-as-given.

---

## Tooling

The library is header-only, so most "quality tooling" here is documentation linting and CI hygiene. The C++ itself is
compiled and exercised by the tests in the [`arm-cortex-mx-core-tests`](https://github.com/embedded-society/arm-cortex-mx-core-tests)
superproject, not in this repo. Everything below runs the same way locally and in CI.

### What is checked, and how

| Concern | Enforced by | Local command |
|---------|-------------|---------------|
| Indentation, charset, final newline, line endings | `.editorconfig` (+ EditorConfig plugin) | Editor-integrated; no command |
| C++ formatting | `.clang-format` | `clang-format -i include/arm-cortex-m0-core/*.hpp` |
| Markdown correctness | `markdownlint-cli2` (pinned in `package.json`) | `npm run lint` / `task lint` |
| The library compiles and behaves | The `arm-cortex-mx-core-tests` test suite | See `CONTRIBUTING.md` § Testing Your Change |
| CI itself | `.github/workflows/*.yml` | Runs on PR and on `main` |

### Pinned versions

Lint tooling is pinned in `package-lock.json`; `npm ci` installs the exact version CI uses. Do not run
`npm install` (which can drift the lockfile) — use `npm ci` so local and CI stay bit-for-bit identical.
Dependabot keeps the pins current; version bumps arrive as reviewable PRs.

### Task runner (optional convenience)

`Taskfile.yml` provides thin wrappers over the npm scripts for those who use [Task](https://taskfile.dev):

```bash
task # list available tasks
task install # npm ci (skipped when node_modules is up to date)
task lint # lint all Markdown
task fix # auto-fix fixable Markdown violations
```

Task is entirely optional — the underlying `npm run` commands are the source of truth and are what CI invokes.

---

*Last updated: 2026-07-04.*
