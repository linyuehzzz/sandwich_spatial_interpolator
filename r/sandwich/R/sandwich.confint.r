#' @title Calculate confidence interval of the Sandwich estimates
#'
#' @description
#' \code{sandwich.confint} calculates the confidence interval of estimated mean value for each reporting unit.
#'
#' @param object An \code{sf} object generated from the \code{sandwich.model} function.
#' @param level The confidence level required. By default, \code{level} = .95.
#'
#' @usage sandwich.confint(object, level=.95)
#'
#' @import sf
#' @importFrom qt
#' @name sandwich.confint
#' @export
#
# ---- End of roxygen documentation ----

sandwich.confint <- function(object, level=.95){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Calculate confidence intervals ----------------------
  t = qt(level, object$df)
  t[is.nan(t)] = 0
  object$ci.low = object$mean - t * object$se
  object$ci.up = object$mean + t * object$se
  object
}
