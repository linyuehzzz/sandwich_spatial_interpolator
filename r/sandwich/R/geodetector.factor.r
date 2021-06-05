#' @title Calculate Geodetector factor detector \emph{q}-statistic
#'
#' @description
#' \code{geodetector.factor} calculates the factor detector \emph{q}-statistic in the geographical detector model described by Wang et al. (2010). The \emph{q}-statistic measures the SSH of the sampling attribute in terms of a given stratification, which can be used for the selection of an SSH layer for Sandwich model-based mapping.
#'
#' @usage geodetector.factor(object, y, x)
#'
#' @param object A POINT \code{sf} object linking the attributes of the sampling layer and the strata ID in the SSH layer(s) generated from \code{geodetector.data}.
#' @param y A \code{string} denoting the name of the explained variable (sampling attribute) in \code{object}.
#' @param x A \code{string} denoting the name(s) of the explanatory variable(s) (stratification(s)) in \code{object}.
#'
#' @references
#' Wang, J. F., Li, X. H., Christakos, G., Liao, Y. L., Zhang, T., Gu, X., & Zheng, X. Y. (2010). Geographical detectors-based health risk assessment and its application in the neural tube defects study of the Heshun Region, China. \emph{International Journal of Geographical Information Science}, 24(1), 107-127. doi:\link[https://doi.org/10.1080/13658810802443457]{10.1080/13658810802443457}
#'
#' @seealso \link[https://cran.r-project.org/package=geodetector]{geodetector R package}
#' @import sf, geodetector
#' @name geodetector.factor
#' @export
#
# ---- End of roxygen documentation ----

geodetector.factor <- function(object, y, x){

  #--------------------------- Check inputs ----------------------------------
  if (st_geometry_type(object, by_geometry=FALSE) != "POINT"){
    stop("Geometry type of the input object should be POINT.")
  }

  #---------------- Calculating factor detector ----------------------
  st_geometry(object) = NULL
  object = as.data.frame(object)

  factor_detector(y, x, object)
}
