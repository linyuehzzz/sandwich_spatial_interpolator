
<!-- README.md is generated from README.Rmd. Please edit that file -->

# Sandwich

<!-- badges: start -->

<!-- badges: end -->

The goal of Sandwich is to …

## Installation

You can install the released version of sandwich from
[CRAN](https://CRAN.R-project.org) with:

``` r
# install.packages("devtools")
library(devtools)
install_github("linyuehzzz/sandwich_spatial_interpolator", subdir="r/Sandwich")
```

And the development version from [GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("yuelinnnnnnn/sandwich_spatial_interpolator")
```

## Example

This is a basic example which shows you how to solve a common problem:

``` r
library(Sandwich)
#> Loading required package: sf
#> Warning: package 'sf' was built under R version 4.0.5
#> Linking to GEOS 3.9.0, GDAL 3.2.1, PROJ 7.2.1
#> Loading required package: ggplot2
#> Warning: package 'ggplot2' was built under R version 4.0.5
#> Loading required package: gridExtra
#> Warning: package 'gridExtra' was built under R version 4.0.5
#> Loading required package: geodetector
#> Warning: package 'geodetector' was built under R version 4.0.5
#> Loading required package: dplyr
#> Warning: package 'dplyr' was built under R version 4.0.5
#> 
#> Attaching package: 'dplyr'
#> The following object is masked from 'package:gridExtra':
#> 
#>     combine
#> The following objects are masked from 'package:stats':
#> 
#>     filter, lag
#> The following objects are masked from 'package:base':
#> 
#>     intersect, setdiff, setequal, union
#> Loading required package: caret
#> Warning: package 'caret' was built under R version 4.0.5
#> Loading required package: lattice
#> Loading required package: lwgeom
#> Warning: package 'lwgeom' was built under R version 4.0.5
#> Linking to liblwgeom 3.0.0beta1 r16016, GEOS 3.9.0, PROJ 7.2.1
## basic example code
```

What is special about using `README.Rmd` instead of just `README.md`?
You can include R chunks like so:

``` r
summary(cars)
#>      speed           dist       
#>  Min.   : 4.0   Min.   :  2.00  
#>  1st Qu.:12.0   1st Qu.: 26.00  
#>  Median :15.0   Median : 36.00  
#>  Mean   :15.4   Mean   : 42.98  
#>  3rd Qu.:19.0   3rd Qu.: 56.00  
#>  Max.   :25.0   Max.   :120.00
```

You’ll still need to render `README.Rmd` regularly, to keep `README.md`
up-to-date. `devtools::build_readme()` is handy for this. You could also
use GitHub Actions to re-render `README.Rmd` every time you push. An
example workflow can be found here:
<https://github.com/r-lib/actions/tree/master/examples>.

You can also embed plots, for example:

<img src="man/figures/README-pressure-1.png" width="100%" />

In that case, don’t forget to commit and push the resulting figure
files, so they display on GitHub and CRAN.
