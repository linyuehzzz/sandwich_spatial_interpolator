#' @title Plot confidence interval for the mean
#'
#' @description
#' \code{sandwich.plot.ci} plots the lower and upper bounds of the confidence interval for the mean value of each reporting unit.
#'
#' @param object An \code{sf} object generated from the \code{sandwich.ci} function.
#'
#' @usage sandwich.plot.ci(object)
#'
#' @import sf ggplot2
#' @importFrom gridExtra grid.arrange
#' @name sandwich.plot.ci
#' @export
#
# ---- End of roxygen documentation ----

sandwich.plot.ci <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Plot Sandwich confidence intervals ----------------------
  p1 = ggplot(data=object) + geom_sf(aes(fill=ci.low)) + labs(fill='Lower bound\nof C.I.') + ggtitle("Confidence Interval (Lower Bound)") + theme(plot.title=element_text(hjust=0.5)) + scale_fill_gradient(low = 'white', high = 'red')

  p2 = ggplot(data=object) + geom_sf(aes(fill=ci.up)) + labs(fill='Upper bound\nof C.I.') + ggtitle("Confidence Interval (Upper Bound)") + theme(plot.title=element_text(hjust=0.5)) + scale_fill_gradient(low = 'white', high = 'red')

  grid.arrange(p1, p2, nrow=1)
}
