#' @title Plot standard error of the Sandwich estimates
#'
#' @description
#' \code{sandwich.plot.se} plots the standard error of the estimated mean value for each reporting unit.
#'
#' @param object An \code{sf} object generated from the \code{sandwich.model} function.
#'
#' @usage sandwich.plot.se(object)
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534.
#'
#' @import sf ggplot2
#' @name sandwich.plot.se
#' @export
#'
#' @examples
#' data(hs.data)
#' hs.sw <- sandwich.model(object=hs.data, sampling.attr="Population", type="shp")
#' sandwich.plot.se(object=hs.sw)
#'
# ---- End of roxygen documentation ----

sandwich.plot.se <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Plot Sandwich standard errors ----------------------
  ggplot(data=object) + geom_sf(aes(fill=se)) + labs(fill='S.E.') + ggtitle("Standard Error") + theme(plot.title=element_text(hjust=0.5)) + scale_fill_gradient(low = 'white', high = 'red')

}
