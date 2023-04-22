#' Plot prediction results
#'
#' @description
#' Plot the estimated mean and standard error for each reporting unit.
#'
#' @param object A \code{sandwich.model} object generated by \code{\link{sandwich.model}}.
#' @param titles A list of texts for the titles.
#' @param labels A list of texts for the legend labels.
#' @param border_color Color for outlines of the polygons.
#' @param poly_fill_mean A list of colors for low and high ends of the gradient in the mapping of means.
#' @param poly_fill_se A list of colors for low and high ends of the gradient in the mapping of standard errors.
#' @param ... Ignored.
#'
#' @examples
#' library(ggplot2)
#' data(sim.data)
#' sim.sw <- sandwich.model(object=sim.data, sampling.attr="Value", type="shp")
#' ggplot2::autoplot(object=sim.sw)
#'
#'
#' @return A list of \code{ggplot} objects.
#'
#' @references
#' Wang, J. F., Haining, R., Liu, T. J., Li, L. F., & Jiang, C. S. (2013). Sandwich estimation for multi-unit reporting on a stratified heterogeneous surface. \emph{Environment and Planning A}, 45(10), 2515-2534.
#'
#' @seealso \code{\link{sandwich.model}}
#'
#' @name autoplot
#'
NULL
# ---- End of roxygen documentation ----

#' @import sf ggplot2
#' @importFrom gridExtra grid.arrange
#' @method autoplot sandwich.model
#' @export
#' @rdname autoplot
autoplot.sandwich.model <- function(object, titles=c("Mean","Standard Error"),
                                    labels=c("",""), border_color="darkgray",
                                    poly_fill_mean=c("white","red"),
                                    poly_fill_se=c("white","blue"), ...){

  #--------------------------- Check inputs ----------------------------------
  if (!is.element("mean", names(object$object)) |
      !is.element("se", names(object$object)) |
      !is.element("df", names(object$object))){
    stop("Should run the sandwich.model function first.")
  }

  #---------------- Plot Sandwich estimates ----------------------
  p1 = ggplot(data=object$object, aes(fill=.data$mean), color=border_color) +
    geom_sf() + labs(fill=labels[1]) +
    ggtitle(titles[1]) +
    theme(plot.title=element_text(hjust=0.5, size=10),
          axis.text.x=element_blank(), axis.text.y=element_blank(),
          axis.ticks=element_blank(), rect=element_blank()) +
    scale_fill_gradient(low=poly_fill_mean[1], high=poly_fill_mean[2])

  #---------------- Plot Sandwich standard errors ----------------------
  p2 = ggplot(data=object$object, aes(fill=.data$se), color=border_color) +
    geom_sf() + labs(fill=labels[1]) +
    ggtitle(titles[2]) +
    theme(plot.title=element_text(hjust=0.5, size=10),
          axis.text.x=element_blank(), axis.text.y=element_blank(),
          axis.ticks=element_blank(), rect=element_blank()) +
    scale_fill_gradient(low=poly_fill_se[1], high=poly_fill_se[2])

  grid.arrange(p1, p2, nrow=1)
}
