# Contributing guidelines

## Tooling

The code is in C++ 23. We use `CMake` as the build system, `Conan` as the package
manager, `clang-format` as the formatter and `clang-tidy` as the linter. For issue
tracking we will probably use `Jira`, although I'd be much happier with 
`GitHub Issues`, so we'll see. We write unit tests in `Google Test`.

### Qt

Installing Qt with `Conan` turned out to be a pain. That's why you **have to**
install it yourself from with the official installer. You can find it on
[Qt's website](https://www.qt.io/development/download-qt-installer-oss).
For this project we are using Qt version **6.11.0**.

## Git

Every issue should be resolved on a seperate branch. You should never push to
neither dev, nor main. After you solve the issue, you should open a pull request
to the `dev` branch on GitHub, linking to the issue tracker's entry (Jira/GitHub
Issues). The code needs to:
 * pass all unit tests
 * be formatted using clang-format
 * not raise any linter errors
 * be verified and accepted by me (Pietrek14)
Furthermore, if you are introducing a new functionality, you should also add
unit tests for it.

If you branch off of your own branch, you don't need to open a pull request to
merge it, but you should still stick to the naming conventions.

## Unit tests

You should probably write unit tests to all non-UI features you write.
The test suite should be named after the tested feature.

### Branch naming conventions

Branch names should *obviously* be descriptive. Don't use abbriviations.
They should be in English. They should be lower-kebab-case. The branch
name should be prefixed by:
 * `feature/` - if the branch introduces a new feature;
 * `bugfix/` - if the branch fixes a bug;
 * `docs/` - if the branch is about project documentation (e.g. this file);
 * `config/` - if the branch's main purpose is to configure a tool (e.g. CMake);
 * `other/` - never - if some use case wasn't included in this list, you
 should first add it to this list in another pull request.

## Application design

The design in Figma can be accessed through
[this link](https://www.figma.com/design/LblymqrUvXdxWcJ1oXwqXO/epsilon?node-id=12-81&t=pgZokOFpwr9GKXF6-1).
If you want to design something yourself, you can ask me (Pietrek14)
for edit permissions. When implementing a view, adhere to the design
as close as possible. The design is desktop-only as of now, responsiveness
is not yet a priority.

## Style

Consult the style guide at `STYLE.md`.
