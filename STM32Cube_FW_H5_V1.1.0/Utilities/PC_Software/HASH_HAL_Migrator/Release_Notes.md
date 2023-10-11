---
pagetitle: HASH HAL Migrator
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}


<center>
# Release Notes for HASH HAL Migrator utility
Copyright &copy; 2023 STMicroelectronics\

[![ST logo](_htmresc/st_logo.png)](https://www.st.com){.logo}
</center>

# Purpose

This PC_Sowftware tool aims to help user to migrate its HASH application to use the new HASH HAL drivers.

The HASH_HAL_Migrator parses the HASH structures, APIs and macros used in a given project that the user specify as input.

Once identified, the tool will replace the legacy definitions with their corresponding ones in the new HAL HASH drivers.

The original files are renamed into *_org.c/.h (ie: main.c renamed into main_org.c). The modification are applied into the original file.

In case a legacy feature is no more supported (ie: MD5), the tool display a warning message and keep the legacy API so the user get a compilation error and fix it.

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section1" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">V1.0.0 / 24-January-2023</label>
<div>

## Main Changes

-	First official release of HASH_HAL_Migrator

## Dependencies

-	To use this tool, the following tools need to be installed
	-	Python v3.9 or greater
	-	colorama V0.3.7 or greater
</div>
:::


:::
:::

<footer class="sticky">
For complete documentation on STM32,visit: [[www.st.com/stm32](http://www.st.com)]

This release note uses up to date web standards and, for this reason, should not be opened with Internet Explorer
but preferably with popular browsers such as Google Chrome, Mozilla Firefox, Opera or Microsoft Edge.
</footer>
