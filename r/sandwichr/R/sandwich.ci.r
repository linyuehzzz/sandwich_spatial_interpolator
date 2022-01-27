#' @title Calculate confidence interval for the mean
#'
#' @description
#' \code{sandwich.ci} calculates the confidence interval for the mean value of each reporting unit.
#'
#' @param object An \code{sf} object or a data frame generated from the \code{sandwich.model} function.
#' @param level The confidence level required. By default, \code{level} = .95.
#'
#' @usage sandwich.ci(object,
#'                    level=.95)
#'
#' @import sf
#' @importFrom stats qt
#' @name sandwich.ci
#' @export
#'
#' @examples
#' data(hs.data)
#' hs.sw <- sandwich.model(object=hs.data, sampling.attr="Population", type="shp")
#' hs.sw.ci <- sandwich.ci(object=hs.sw, level=.95)
#'
# ---- End of roxygen documentation ----

sandwich.ci <- function(object, level=.95){
  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object$object)) |
      !is.element("se", names(object$object)) |
      !is.element("df", names(object$object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Calculate confidence intervals ----------------------
  t = qt(1-(1-level)/2, object$object$df)
  t[is.nan(t)] = 0
  object$object$ci.low = object$object$mean - t * object$object$se
  object$object$ci.up = object$object$mean + t * object$object$se

  output = list(object=object)
  class(output) <- "sandwich.ci"
  return(output)
}
