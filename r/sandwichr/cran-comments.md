## 2022/01/27
>   If there are references describing the methods in your package, please add these in the description field of your DESCRIPTION file in the form authors 	    (year) <doi:...> authors (year) <arXiv:...> authors (year, ISBN:...) or if those are not available: <https:...> with no space after 'doi:', 'arXiv:',     'https:' and angle brackets for auto-linking.

Thank you for the comment. We added the reference of Wang et al. (2013) <doi:10.1068/a44710> in the description.

>   Please add \value to .Rd files regarding exported methods and explain the functions results in the documentation. Please write about the structure of     the output (class) and also what the output means. (If a function does not return a value, please document that too, e.g. 
    \value{No return value, called for side effects} or similar) Missing Rd-tags in up to 11 .Rd files, e.g.:
      load.data.shp.Rd: \value
      load.data.txt.Rd: \value
      sandwich.ci.Rd: \value
      sandwich.cv.Rd: \value
      sandwich.model.Rd: \value
      sandwich.plot.ci.Rd: \value
      ...

We added the @return tags to all the functions to demonstrate their outputs.


## Test environments
* local R installation, R 4.0.4
* ubuntu 16.04 (on travis-ci), R 4.0.4
* win-builder (devel)

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
