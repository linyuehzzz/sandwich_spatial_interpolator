#' @title Calculate Geodetector factor detector \emph{q}-statistic and interaction detector
#'
#' @description
#' \code{ssh.test} calculates the factor detector \emph{q}-statistic and the interaction detector in the geographical detector model described by Wang et al. (2010). The \emph{q}-statistic measures the SSH of the sampling attribute in terms of a given stratification, which can be used for the selection of an SSH layer for Sandwich model-based mapping. The interactive effects indicate whether a combination of two stratifications enhances the SSH of the sampling attribute.
#'
#' @usage ssh.test(object,
#'                 y,
#'                 x,
#'                 test="factor",
#'                 type="shp")
#'
#' @param object A POINT \code{sf} object linking the attributes of the sampling layer and the strata ID in the SSH layer(s) generated from \code{ssh.data}.
#' @param y A \code{string} denoting the name of the explained variable (sampling attribute) in \code{object}.
#' @param x A \code{string} denoting the name(s) of the explanatory variable(s) (stratification(s)) in \code{object}.
#' @param test A \code{string} denoting the type of test. \code{test="factor"} denotes the factor detector, and \code{test="interaction"} denotes the interaction detector. By default, \code{test="factor"}.
#' @param type A \code{string} denoting the type of input data. \code{type="shp"} denotes shapefiles, and \code{type="txt"} denotes text files. By default, \code{type="shp"}.
#'
#' @references
#' Wang, J. F., Li, X. H., Christakos, G., Liao, Y. L., Zhang, T., Gu, X., & Zheng, X. Y. (2010). Geographical detectors-based health risk assessment and its application in the neural tube defects study of the Heshun Region, China. \emph{International Journal of Geographical Information Science}, 24(1), 107-127.
#'
#' @seealso [https://cran.r-project.org/package=geodetector]{geodetector R package}
#' @import sf geodetector
#' @name ssh.test
#' @export
#'
#' @examples
#' library(sf)
#' library(tools)
#' data(hs.data)
#' hs.ssh2.name <- system.file("extdata", "hs.ssh2.shapefile.shp",
#'                             package="sandwichr")
#' hs.ssh2 <- read_sf(dsn=dirname(hs.ssh2.name),
#'                   layer=file_path_sans_ext(basename(hs.ssh2.name)))
#' hs.join <- ssh.data.shp(object=hs.data[[1]], ssh.lyr=hs.data[[2]], ssh.id="STR_1")
#' hs.join <- ssh.data.shp(object=hs.join, ssh.lyr=hs.ssh2, ssh.id="STR_2")
#' ssh.test(object=hs.join, y="Population", x=c("STR_1", "STR_2"), test="factor")
#'
# ---- End of roxygen documentation ----

ssh.test <- function(object, y, x, test="factor", type="shp"){
  if (type == "shp"){
    #--------------------------- Check inputs ----------------------------------
    if (st_geometry_type(object, by_geometry=FALSE) != "POINT"){
      stop("Geometry type of the input object should be POINT.")
    }

    st_geometry(object) = NULL
    object = as.data.frame(object)
  }

  #---------------- Calculating factor detector ----------------------
  if (test == "factor"){
    factor_detector(y, x, object)
  }
  else if (test == "interaction"){
    interaction_detector(y, x, object)
  }
}
