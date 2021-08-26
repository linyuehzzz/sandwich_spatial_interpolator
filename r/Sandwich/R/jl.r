#' Jilin rodent density dataset
#'
#' The \code{jl} dataset consists of four \code{sf} objects:
#' \itemize{
#' \item\code{jl.sampling}: Rodent density at 627 sampling quadrats in Jilin, China, which serves as the sampling layer.
#' \item\code{jl.ssh}: A classification map with 8 strata that serves as a candidate SSH layer.
#' \item\code{jl.ssh2}: A zonation map with 11 strata that serves as another candidate SSH layer.
#' \item\code{jl.reporting}: The administrative division of 10 counties in Jilin that served as the reporting layer.}
#'
#' @references Liu, T., Wang, J., Xu, C., Ma, J., Zhang, H., & Xu, C. (2018). Sandwich mapping of rodent density in Jilin Province, China. \emph{Journal of Geographical Sciences}, 28(4), 445-458.. doi:\link[https://doi.org/10.1007/s11442-018-1483-z]{10.1007/s11442-018-1483-z}
#'
#' @import sf
#' @docType data
#' @name jl
#' @examples
#' library(sf)
#' library(ggplot2)
#' data("jl.sampling")
#' summary(jl.sampling$Shushu)
#' ggplot(data=jl.sampling) + geom_sf(aes(color=Shushu))
NULL
