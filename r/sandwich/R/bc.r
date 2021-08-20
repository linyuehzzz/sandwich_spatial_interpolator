#' Breast cancer incidence in mainland China
#'
#' The \code{bc} dataset consists of three \code{sf} objects:
#' \itemize{
#' \item\code{bc.sampling}: Breast cancer incidence at 271 sampling units in mainland China, which serves as the sampling layer.
#' \item\code{bc.ssh}: A classification map with 20 strata that serves as a candidate SSH layer.
#' \item\code{bc.reporting}: The administrative division of 32 provices in mainland China that served as the reporting layer.}
#'
#' @import sf
#' @docType data
#' @name bc
#' @examples
#' library(sf)
#' library(ggplot2)
#' data("bc.sampling")
#' summary(bc.sampling$Incidence)
#' ggplot(data=bc.sampling) + geom_sf(aes(color=Incidence))
NULL
