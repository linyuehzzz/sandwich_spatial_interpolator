#' @title Calculate confidence interval of the Sandwich estimates
#'
#' @description
#' \code{sandwich.ci} calculates the confidence interval of estimated mean value for each reporting unit.
#'
#' @param object An \code{sf} object generated from the \code{sandwich.model} function.
#' @param level The confidence level required. By default, \code{level} = .95.
#'
#' @usage sandwich.ci(object, level=.95)
#'
#' @import sf
#' @importFrom qt
#' @name sandwich.ci
#' @export
#
# ---- End of roxygen documentation ----

sandwich.ci <- function(object, level=.95){
  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Calculate confidence intervals ----------------------
  t = qt(1-(1-level)/2, object$df)
  t[is.nan(t)] = 0
  object$ci.low = object$mean - t * object$se
  object$ci.up = object$mean + t * object$se
  object
}
