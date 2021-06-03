#' @title Plot confidence interval of the Sandwich estimates
#'
#' @description
#' \code{plot.ci} plots the confidence interval of estimated mean value for each reporting unit.
#'
#' @param object \code{sf} object generated from the \code{sandwich.confint} function.
#'
#' @usage \code{plot.ci(object, level=.95)}
#'
#' @import sf, ggplot2, gridExtra
#' @name plot.ci
#' @export
#
# ---- End of roxygen documentation ----

plot.ci <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Plot Sandwich confidence intervals ----------------------
  p1 = ggplot(data=object) + geom_sf(aes(fill=ci.low)) + labs(fill='Lower bound\nof C.I.')
  p2 = ggplot(data=object) + geom_sf(aes(fill=ci.high)) + labs(fill='Higher bound\nof C.I.')
  grid.arrange(p1, p2, nrow = 1)
}
