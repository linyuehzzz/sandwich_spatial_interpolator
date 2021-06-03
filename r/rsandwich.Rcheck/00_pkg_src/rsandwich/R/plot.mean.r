#' @title Plot Sandwich estimates
#'
#' @description
#' \code{plot.mean} plots the mean value of an attribute for each reporting unit estimated by the Sandwich model.
#'
#' @param object Updated reporting layer generated from the \code{sandwich} function.
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534. doi:\link[https://doi.org/10.1068/a44710]{10.1068/a44710}
#'
#' @import sf, ggplot2
#' @name plot.mean
#' @export
#
# ---- End of roxygen documentation ----

plot.mean <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Plot Sandwich estimates ----------------------
  ggplot(data=object) + geom_sf(aes(fill=mean))

}
