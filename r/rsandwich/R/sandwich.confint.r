#' @title Calculate confidence interval of the Sandwich estimates
#'
#' @description
#' \code{sandwich.confint} calculates the confidence interval of estimated mean value for each reporting unit.
#'
#' @param object \code{sf} object generated from the \code{sandwich} function.
#' @param level The confidence level required.
#'
#' @usage \code{sandwich.confint(object, level=.95)}
#'
#' @import sf
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

  #---------------- Plot Sandwich estimates ----------------------
  t = qt(level, object$df)
  object$ci.low = object$mean - t * object$se
  object$ci.high = object$mean + t * object$se
  object
}
