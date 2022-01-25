
<!-- README.md is generated from README.Rmd. Please edit that file -->

# sandwichr: Spatial interpolation based on spatial stratified heterogeneity

<!-- badges: start -->

[![Lifecycle:
stable](https://img.shields.io/badge/lifecycle-stable-brightgreen.svg)](https://lifecycle.r-lib.org/articles/stages.html#stable)
<!-- [![R-CMD-check](https://github.com/linyuehzzz/sandwich_spatial_interpolator/workflows/R-CMD-check/badge.svg)](https://github.com/linyuehzzz/sandwich_spatial_interpolator/actions) -->
<!-- badges: end -->

`sandwichr` is an R package for spatial interpolation based on the
[spatial stratified heterogeneity (SSH)](http://www.geodetector.cn/)
theory, which enables users to:

  - Interpolate the sampling attribute over the reporting units that
    does not rely on spatial autocorrelation;
  - Assess the interpolation uncertainties through standard errors and
    confidence intervals;
  - Evaluate the overall accuracy using a diagnostic statistic called
    the k-fold cross validation estimate.

## Getting setup with R

Using the `sandwichr` package requires a recent version of R to be
installed on your computer. The easiest way is to install it through
[CRAN](https://cran.r-project.org/) , which stands for the Comprehensive
R Archive Network.

  - For Windows, visit <https://cran.r-project.org/bin/windows/base/>.
  - For macOS, visit <https://cran.r-project.org/bin/macosx/>.
  - For Linux, visit
    <https://cran.r-project.org/doc/manuals/r-release/R-admin.html>.

Once R is installed, you can proceed to install the RStudio Integrated
Development Environment (IDE) to have a much improved environment to
work with R. [Here](https://www.rstudio.com/products/rstudio/) is
detailed description of RStudio. It is free to download on
<https://www.rstudio.com/products/rstudio/download/#download>.

## Installing the package

Now you have the base R and a nice IDE installed on your computer, you
can navigate to the console window (in RStudio, the bottom left panel)
and install the `sandwichr` package from source code by executing the
following lines of code:

``` r
require(devtools)
install_github("linyuehzzz/sandwich_spatial_interpolator", subdir="r/sandwichr", build_vignettes = TRUE)
```

## Tutorial

Once you install the package, we strongly recommend you going through a
tutorial of this package to explore it in different scenarios of use.
You can find it using the argument:

``` r
browseVignettes("sandwichr")
```

A manual of the `sandwichr` package can be found
[here](https://github.com/linyuehzzz/sandwich_spatial_interpolator/blob/master/r/sandwichr_1.0.0.pdf),
which introduces all the available functions in this package.

## Citation

Please cite the following reference if you use the code. We are also
working on an article about this particular software.

    @article{Wang+Haining+Liu+Li+Jiang:2013,
        author = {Jin-Feng Wang and Robert Haining and Tie-Jun Liu and Lian-Fa Li and Cheng-Sheng Jiang},
        title ={Sandwich Estimation for Multi-Unit Reporting on a Stratified Heterogeneous Surface},
        journal = {Environment and Planning A: Economy and Space},
        volume = {45},
        number = {10},
        pages = {2515-2534},
        year = {2013},
        doi = {10.1068/a44710}
    }

## Contacts

If there are any questions or suggestions (or anything else you want to
talk about concerning this project), please feel free to let us know\!
If you have found a bug, you can also file an
[issue](https://github.com/linyuehzzz/sandwich_spatial_interpolator/issues).

**Email**: lin.3326@osu.edu (Ms Yue Lin), xucd@lreis.ac.cn (Dr Chengdong
Xu), wangjf@lreis.ac.cn (Dr Jinfeng Wang\*)

State Key Laboratory of Resources and Environmental Information System  
Institute of Geographic Sciences and Natural Resources Research  
Chinese Academy of Sciences  
Beijing, 100101, China
