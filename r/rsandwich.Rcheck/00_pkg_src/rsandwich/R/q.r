#' @title Plot Sandwich estimates
#'
#' @description
#' \code{plot.mean} plots the mean value of an attribute for each reporting unit estimated by the Sandwich model.
#'
#' @param object Updated reporting layer generated from the \code{sandwich} function.
#'
#' @references
#' Wang, J. F., Li, X. H., Christakos, G., Liao, Y. L., Zhang, T., Gu, X., & Zheng, X. Y. (2010). Geographical detectors‐based health risk assessment and its application in the neural tube defects study of the Heshun Region, China. International Journal of Geographical Information Science, 24(1), 107-127. doi:\link[https://doi.org/10.1080/13658810802443457]{10.1080/13658810802443457}
#' @examples
#' library(sf)
#' data("hs.sampling")
#' data("hs.ssh")
#' data("hs.reporting")
#' sandwich(hs.sampling, hs.ssh, hs.reporting, "Population")
#'
#' @import sf
#' @name q
#' @export
#
# ---- End of roxygen documentation ----

q <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element(sampling.attr, names("mean")) |
      !is.element(sampling.attr, names("se"))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Calculating sample means and SEs for SSH layer ----------------------

}
