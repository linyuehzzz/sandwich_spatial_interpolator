#' @title Calculate Geodetector factor detector \emph{q}-statistic and interaction detector
#'
#' @description
#' \code{ssh.test} calculates the factor detector \emph{q}-statistic and the interaction detector in the geographical detector model described by Wang et al. (2010). The \emph{q}-statistic measures the SSH of the sampling attribute in terms of a given stratification, which can be used for the selection of an SSH layer for Sandwich model-based mapping. The interactive effects indicate whether a combination of two stratifications enhances the SSH of the sampling attribute.
#'
#' @usage ssh.test(object, y, x, test="factor")
#'
#' @param object A POINT \code{sf} object linking the attributes of the sampling layer and the strata ID in the SSH layer(s) generated from \code{ssh.data}.
#' @param y A \code{string} denoting the name of the explained variable (sampling attribute) in \code{object}.
#' @param x A \code{string} denoting the name(s) of the explanatory variable(s) (stratification(s)) in \code{object}.
#' @param test A \code{string} denoting the type of test. \code{test="factor"} denotes the factor detector, and \code{test="interaction"} denotes the interaction detector. By default, \code{test="factor"}.
#'
#' @references
#' Wang, J. F., Li, X. H., Christakos, G., Liao, Y. L., Zhang, T., Gu, X., & Zheng, X. Y. (2010). Geographical detectors-based health risk assessment and its application in the neural tube defects study of the Heshun Region, China. \emph{International Journal of Geographical Information Science}, 24(1), 107-127. doi:\link[https://doi.org/10.1080/13658810802443457]{10.1080/13658810802443457}
#'
#' @seealso \link[https://cran.r-project.org/package=geodetector]{geodetector R package}
#' @import sf, geodetector
#' @name ssh.test
#' @export
#
# ---- End of roxygen documentation ----

ssh.test <- function(object, y, x, test="factor"){

  #--------------------------- Check inputs ----------------------------------
  if (st_geometry_type(object, by_geometry=FALSE) != "POINT"){
    stop("Geometry type of the input object should be POINT.")
  }

  #---------------- Calculating factor detector ----------------------
  st_geometry(object) = NULL
  object = as.data.frame(object)
  if (test == "factor"){
    factor_detector(y, x, object)
  }
  else if (test == "interaction"){
    interaction_detector(y, x, object)
  }
}
