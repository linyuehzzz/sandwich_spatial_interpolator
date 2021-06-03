#' @title Perform Sandwich model-based mapping
#'
#' @description
#' \code{sandwich} estimate the mean value of an attribute and its standard error for each reporting unit using the Sandwich method documented by Wang et al. (2013).
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
#' @name sandwich
#' @export
#
# ---- End of roxygen documentation ----


sandwich <- function(sampling.lyr, ssh.lyr, reporting.lyr, sampling.attr){

#--------------------------- Check inputs ----------------------------------
if (st_geometry_type(sampling.lyr, by_geometry=FALSE) != "POINT"){
  stop("Geometry type of the sampling layer should be POINT.")
}
if (st_geometry_type(ssh.lyr, by_geometry=FALSE) != "POLYGON"){
  stop("Geometry type of the SSH layer should be POLYGON.")
}
if (st_geometry_type(reporting.lyr, by_geometry=FALSE) != "POLYGON"){
  stop("Geometry type of the reporting layer should be POLYGON.")
}
if (!is.element(sampling.attr, names(sampling.lyr))){
  stop("Attribute name not found in the sampling layer.")
}

#---------------- Calculating sample means and SEs for SSH layer ----------------------
ssh.lyr$mean = 0
ssh.lyr$se = 0
for (i in 1:(nrow(ssh.lyr))){
  z.pts = st_intersection(sampling.lyr, ssh.lyr[i,])
  ssh.lyr[i,]$mean = mean(z.pts[[sampling.attr]])
  z.v = var(z.pts[[sampling.attr]])
  ssh.lyr[i,]$se = sqrt(z.v / nrow(z.pts))
}
# print(ssh.lyr$mean)
# print(ssh.lyr$se)


#---------------- Calculating values and SEs for reporting layer -----------------
reporting.lyr$mean = 0
reporting.lyr$se = 0
for (i in 1:(nrow(reporting.lyr))){
  z.mean = z.se = 0
  for (j in 1:(nrow(ssh.lyr))){
    if (st_intersects(ssh.lyr[j,], reporting.lyr[i,], sparse = FALSE)[1]){
      r.poly = st_intersection(ssh.lyr[j,], reporting.lyr[i,])
      r.w = as.numeric(st_area(r.poly)) / as.numeric(st_area(reporting.lyr[i,]))
      reporting.lyr[i,]$mean = reporting.lyr[i,]$mean + r.w * ssh.lyr[j,]$mean
      reporting.lyr[i,]$se = reporting.lyr[i,]$se + r.w ^2 * ssh.lyr[j,]$mean^2
    }
    reporting.lyr[i,]$se = sqrt(reporting.lyr[i,]$se)
  }
}
reporting.lyr
}
