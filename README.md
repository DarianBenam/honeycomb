# Honeycomb

`Honeycomb` is a cross-platform sitemap generator console app written in C++20.

## Usage

```console
honeycomb -vi --outputpath [...] --domain [...] --wwwroot [...] --templatedir [...] --ext [...] --engine [...] --llpath [...] --ilpath [...]
```

## Runtime Flag Variables

### Single Character Flags

A single character flag is passed into the app via the `-` prefix. Single character flags can be daisy-chained together as each letter is evaluated
separately.

| Flag | Description                                          | Required |
|------|------------------------------------------------------|----------|
| `v`  | Runs `honeycomb` in verbose mode.                    | ❌        |
| `i`  | Adds indentation to the output sitemap XML file.     | ❌        |

### Multi-character Flags

A multi-character flag is passed into the app via the `--` prefix. Multi-character flags allow a custom variable to be passed into the app.

| Flag          | Description                                                                                                           | Required |
|---------------|-----------------------------------------------------------------------------------------------------------------------|----------|
| `outputpath`  | The path where the sitemap file should be written too. This path must include the file name.                          | ✔️        |
| `domain`      | The domain name which will prefix relative URLs found by `honeycomb`.                                                 | ✔️        |
| `ext`         | Regex pattern for which files should be included in the sitemap. Default value is `.htm\|.html`.                      | ❌        |
| `wwwroot`     | The path to the `wwwroot` root folder of the website.                                                                 | ✔️        |
| `templatedir` | The location where template view files are stored.                                                                    | ❌        |
| `engine`      | The template engine that the view files were written in. At the moment, the only valid value for this flag is `twig`. | ❌        |
| `llpath`      | The path to the link list file. Default value is `.honeycomblinklist`.                                                | ❌        |
| `ilpath`      | The path to the ignore list file. Default value is `.honeycombignorelist`.                                            | ❌        |

## Config Files

## `.honeycombignorelist`

The `.honeycombignorelist` file defines a list of regex patterns that `honeycomb` should ignore when scanning the `wwwroot` and template directories.

### Example

```ini
# Ignore any file ending with error.php
error.php$

# Ignore everything that starts with /api/
^[/\\]api[/\\]
```

## `.honeycomblinklist`

The `.honeycomblinklist` file defines a list of hardcoded relative URLs along with their last modification date. You should define items in this list 
if `honeycomb` is unable to pick it up. An example use case to define URLs in this file is a webpage that is generated via a GET param.

## Example

```ini
/download-preview.php?id=1 2022-01-09
/download-preview.php?id=2 2022-05-24
/download-preview.php?id=3 2022-03-06
```
