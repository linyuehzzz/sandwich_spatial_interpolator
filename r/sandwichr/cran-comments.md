## 2022/11/17
> Found the following (possibly) invalid URLs:
     URL: https://urldefense.com/v3/__https://cran.r-project.org/doc/manuals/r-release/R-admin.html/__;!!KGKeukY!ztCVFwHDCus-qk2WPb5PfMnrJPjGgeiHDNSnisHE-rnaSDunJxR754DaVfIx0lz1nQuit4m-SU9Dmz0PeX6qeLclH9mAutg$ 
       From: README.md
       Status: 404
       Message: Not Found
The trailing slash is certainly wrong.

We fixed the trailing slash.


## 2022/11/17
> Found the following (possibly) invalid URLs:
     URL: 
https://urldefense.com/v3/__https://github.com/linyuehzzz/sandwich_spatial_interpolator/blob/master/r/sandwichr_1.0.1.pdf__;!!KGKeukY!3i9f7-HJh6tj29fjdYHOmCg1AubBbmVjMYUR6o_S4SFmML3FGC3Lh3yEDUZf6Me_Gkl0vdiV3wc_H0HxtDDwMKj20jFZ7lk$ 
       From: README.md
       Status: 404
       Message: Not Found

We removed the link.

>      URL: https://urldefense.com/v3/__https://www.rstudio.com/products/rstudio/__;!!KGKeukY!3i9f7-HJh6tj29fjdYHOmCg1AubBbmVjMYUR6o_S4SFmML3FGC3Lh3yEDUZf6Me_Gkl0vdiV3wc_H0HxtDDwMKj2ohlvV98$  (moved to https://urldefense.com/v3/__https://posit.co/products/open-source/rstudio/__;!!KGKeukY!3i9f7-HJh6tj29fjdYHOmCg1AubBbmVjMYUR6o_S4SFmML3FGC3Lh3yEDUZf6Me_Gkl0vdiV3wc_H0HxtDDwMKj2273ahNA$ )
       From: README.md
       Status: 301
       Message: Moved Permanently
     URL: https://urldefense.com/v3/__https://www.rstudio.com/products/rstudio/download/*download__;Iw!!KGKeukY!3i9f7-HJh6tj29fjdYHOmCg1AubBbmVjMYUR6o_S4SFmML3FGC3Lh3yEDUZf6Me_Gkl0vdiV3wc_H0HxtDDwMKj2sSlJrjM$
(moved to https://urldefense.com/v3/__https://posit.co/download/rstudio-desktop/*download__;Iw!!KGKeukY!3i9f7-HJh6tj29fjdYHOmCg1AubBbmVjMYUR6o_S4SFmML3FGC3Lh3yEDUZf6Me_Gkl0vdiV3wc_H0HxtDDwMKj2BlDA1ko$ )
       From: README.md
       Status: 301
       Message: Moved Permanently

We corrected these links.

> Please change http --> https, add trailing slashes, or follow moved content as appropriate.

We changed all http to https and add trailing slashes to all urls.


> The Date field is over a month old.

We updated the Date.


## 2022/02/08
> Found the following (possibly) invalid URLs:
     URL: 
https://urldefense.com/v3/__https://github.com/linyuehzzz/sandwich_spatial_interpolator/blob/master/r/sandwichr_1.0.0.pdf__;!!KGKeukY!jMgH-sg4q1aoERzDWZmXvX3-i_rmc3c7PfKSGqRmKhbTBv_a13mE73ZxKsqbUug81Q$ 
       From: README.md
       Status: 404
       Message: Not Found

The link was corrected.


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
