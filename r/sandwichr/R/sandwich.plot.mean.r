#' @title Plot Sandwich estimates
#'
#' @description
#' \code{sandwich.plot.mean} plots the mean value of an attribute for each reporting unit estimated by the Sandwich model.
#'
#' @param object An \code{sf} object generated from the \code{sandwich.model} function.
#'
#' @usage sandwich.plot.mean(object)
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534. doi:\link[https://doi.org/10.1068/a44710]{10.1068/a44710}
#'
#' @import sf ggplot2
#' @name sandwich.plot.mean
#' @export
#'
#' @examples
#' data(hs.data)
#' hs.sw <- sandwich.model(object=hs.data, sampling.attr="Population", type="shp")
#' sandwich.plot.mean(object=hs.sw)
#'
# ---- End of roxygen documentation ----

sandwich.plot.mean <- function(object){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object)) |
      !is.element("se", names(object)) |
      !is.element("df", names(object))){
    stop("Should run the sandwich function first.")
  }

  #---------------- Plot Sandwich estimates ----------------------
  ggplot(data=object) + geom_sf(aes(fill=mean)) + labs(fill='Mean') + ggtitle("Mean") + theme(plot.title=element_text(hjust=0.5)) + scale_fill_gradient(low = 'white', high = 'red')

}
