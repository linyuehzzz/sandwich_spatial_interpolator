#' @title Plot standard error of the Sandwich estimates
#'
#' @description
#' \code{plot.se} plots the standard error of estimated mean value for each reporting unit.
#'
#' @param object An \code{sf} object generated from the \code{sandwich} function.
#'
#' @usage plot.se(object)
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534. doi:\link[https://doi.org/10.1068/a44710]{10.1068/a44710}
#'
#' @import sf, ggplot2
#' @importFrom ggplot, geom_sf, labs, aes
#' @name plot.se
#' @export
#
# ---- End of roxygen documentation ----

plot.se <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Plot Sandwich standard errors ----------------------
  ggplot(data=object) + geom_sf(aes(fill=se)) + labs(fill='S.E.') + ggtitle("Standard Error") + theme(plot.title=element_text(hjust=0.5)) + scale_fill_gradient(low = 'white', high = 'red')

}
