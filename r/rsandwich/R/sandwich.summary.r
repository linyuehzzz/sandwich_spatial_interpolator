#' @title Perform Sandwich spatial interpolation
#'
#' @description
#' \code{sandwich} performs spatial interpolation using the Sandwich method documented by Wang et al. (2013).
#'
#' @param sampling.lyr a POINT \code{sf} object used as the sampling layer. It should contain an attribute that is to be interpolated.
#' @param ssh.lyr a POLYGON \code{sf} object used as the SSH layer.
#' @param reporting.lyr a POLYGON \code{sf} object used as the reporting layer.
#' @param sampling.attr name of the attribute in the sampling layer to be interpolated.
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534. doi:\link[https://doi.org/10.1068/a44710]{10.1068/a44710}
#' @examples
#' library(sf)
#' data("hs.sampling")
#' data("hs.ssh")
#' data("hs.reporting")
#' sandwich(hs.sampling, hs.ssh, hs.reporting, "Population")
#'
#' @import sf
#' @name sandwich.summary
#' @export
#
# ---- End of roxygen documentation ----
