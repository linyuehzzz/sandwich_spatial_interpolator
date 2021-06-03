# This is package documentation for rsanwich.
# roxygen will use this file to create a NAMESPACE file.
# Of importance is the @import command, as it lists package dependencies.

#' \code{rsandwich}: Spatial Interpolation of Spatially Stratified Heterogeneous Populations
#'
#' The package \code{rsandwich} provides tools to interpolate a spatially stratified heterogeneous population with high accuracy, even when its spatial autocorrelation is weak. These tools allow the calculation of critical summarized statistics such as Geodetector \emph{q} and Moran's \emph{I}. They also enable the visualization of the interpolated surface and the variance and confidence interval maps.
#'
#' @author Yue Lin, Chengdong Xu and Jinfeng Wang
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534. doi:\link[https://doi.org/10.1068/a44710]{10.1068/a44710}
#'
#' @import sp rgeos maptools spdep rgdal deldir raster grDevices methods
#' @importFrom stats optim
#' @docType package
#' @name rsandwich
NULL
