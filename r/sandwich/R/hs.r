#' Heshun human population
#'
#' The \code{hs} dataset consists of four \code{sf} objects:
#' \itemize{
#' \item\code{hs.sampling}: Human population of 326 sampling villages within the Heshun region, China, which serves as the sampling layer.
#' \item\code{hs.ssh}: A zonation map with 5 strata that serves as a candidate SSH layer.
#' \item\code{hs.ssh2}: A zonation map with 6 strata that serves as another candidate SSH layer.
#' \item\code{hs.reporting}: The administrative division of 10 towns in Heshun county that served as the reporting layer.}
#'
#' @references Li, L., Wang, J., & Wu, J. (2012). A spatial model to predict the incidence of neural tube defects. \emph{BMC Public Health}, 12(1), 951. doi:\link[https://doi.org/10.1186/1471-2458-12-951]{10.1186/1471-2458-12-951}
#'
#' @import sf
#' @docType data
#' @name hs
#' @examples
#' library(sf)
#' library(ggplot2)
#' data("hs.sampling")
#' summary(hs.sampling$Population)
#' ggplot(data=hs.sampling) + geom_sf(aes(color=Population))
NULL
