#' Perform Sandwich spatial interpolation
#'
#' \code{sandwich} performs spatial interpolation using the Sandwich method documented by Wang et al. (2013).
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534. doi:\link[https://doi.org/10.1068/a44710]{10.1068/a44710}
#'
#' @import sf
#' @docType function
#' @name sandwich
#' @export
#
# ---- End of roxygen documentation ----


sandwich <- function(sampling.lyr, ssh.lyr, reporting.lyr, sampling.field){

#--------------------------- Check inputs ----------------------------------

#---------------- Calculating sample means and SEs for SSH layer ----------------------
ssh.lyr$mean = 0
ssh.lyr$se = 0
for (i in 1:(nrow(ssh.lyr))){
  z.pts = st_intersection(sampling.lyr, ssh.lyr[i,])
  ssh.lyr[i,]$mean = mean(z.pts[[sampling.field]])
  v = var(z.pts[[sampling.field]])
  ssh.lyr[i,]$se = sqrt(v / nrow(z.pts))
}
# print(ssh.lyr$mean)
# print(ssh.lyr$se)

#---------------- Calculating values and SEs for reporting layer -----------------
reporting.lyr$mean = 0
reporting.lyr$se = 0
for (i in 1:(nrow(reporting.lyr))){
  r.poly =
  z.pts = st_intersection(sampling.lyr, ssh.lyr[i,])
  ssh.lyr[i,]$mean = mean(z.pts[[sampling.field]])
  v = var(z.pts[[sampling.field]])
  ssh.lyr[i,]$se = sqrt(v / nrow(z.pts))
}

}
