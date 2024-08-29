# Contributing to FSP for Renesas RA MCU Family

Thank you for your interest in contributing to FSP for RA. This document will help you navigate the contribution process.

## Table of Contents

- [Bug Reports](#bug-reports)
- [Feature/Enhancement Requests](#featureenhancement-requests)
- [Contributing Code](#contributing-code)
  - [Signing Contributor License Agreement](#signing-contributor-license-agreement)
  - [Contributing through a Pull Request](#contributing-through-a-pull-request)
- [Technical support](#technical-support)

## Bug Reports

If the bug is a security vulnerability, follow the instructions for reporting a vulnerability [here](https://github.com/renesas/fsp/security).

For all other bugs, [create a Github issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/creating-an-issue). To help us reproduce and address the bug, please include the following information:

- Expected behavior
- Actual behavior
- Steps to reproduce
- Logs/screenshots/measurements (if relevant to the issue)

An FSP maintainer will review the issue and follow up in a comment.

## Feature/Enhancement Requests

We consider all feature requests made through [Github issues](https://docs.github.com/en/issues/tracking-your-work-with-issues/creating-an-issue).

- The FSP team will review your request and may respond with follow-up questions.
- If we determine the feature is a good fit for FSP, we will prioritize and assign it internally.
- When work begins on a feature, we will add a comment to the issue.
- When the feature is included in an FSP release, we will close the issue and add a comment containing the release version that contains the feature.
- Unfortunately, not all feature requests can be implemented. Issues that will not be implemented (ex. not feasible, not a good fit for FSP, insufficient details) will be closed.

If you would like to implement a feature request made by someone else, and work has not already started on that issue, please comment on the issue that you would like to work on it, and your plan for implementation. Then follow the [Contributing Code](#contributing-code) process to make the updates.

## Contributing Code

### Signing Contributor License Agreement

We require community contributors to sign a Contributor License Agreement (CLA). If you or your organization haven't previously signed, a bot comment will prompt you to sign the CLA when you create a pull request.

Ensure a CLA has been signed for your GitHub account by checking the [CLA page](https://cla-assistant.io/renesas/fsp).

### Contributing through a Pull Request

We welcome contributions via Github Pull Requests. If you're interested in contributing, please follow these steps:

1. Make sure the code change is relevant to FSP for the Renesas RA MCU Family
1. Search the Github issues (including closed issues) to confirm the change is not a duplicate of another issue
1. [Create a GitHub issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/creating-an-issue) with details of the proposed features or improvements or comment the planned changes on the existing issue (if applicable)
   - The FSP team will review the plan and either approve it or suggest changes as needed.
   - We highly recommend waiting for FSP team approval for all substantial changes, however if your change is very straightforward (ex. 1-line bug fix), you can make a PR without waiting for approval.
1. [Fork the repository](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo) to your GitHub account for the feature development.
    - Once development is complete, create a [pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork).
 1. The FSP team will review your PR, ask questions if we have any, and perform internal integration and testing.
    - When the change is accepted, we will let you know in a Github comment and close the pull request.

**Important:** If you are contributing multiple independent features/bug fixes, please submit a separate pull request for each item.

## Technical Support

Need help with something other than RA FSP? For general support requests or questions related to Renesas products, tools, or environments, feel free to submit a ticket in our support [system](https://www.renesas.com/us/en/support). We're here to help!
