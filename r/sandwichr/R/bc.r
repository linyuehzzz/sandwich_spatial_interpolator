#' Breast cancer incidence in mainland China
#'
#' The \code{bc} dataset consists of two \code{csv} files:
#' \itemize{
#' \item\code{bc_sampling_ssh}: Breast cancer incidence at 242 sampling units in mainland China, where the SSH stratum (\code{"SSHID"}) and reporting unit (\code{"GBCODE"}) that each sample falls into are specified. The sampling attribute is \code{"Incidence"}.
#' \item\code{bc_reporting_ssh}: The county-level administrative divisions in mainland China (\code{"GBCODE"}), where the weights of each intersecting stratum (\code{"W1"} and \code{"W2"}) are specified.}
#'
#' @import sf
#' @docType data
#' @name bc
NULL
