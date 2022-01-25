#' @title Load text files into data frames
#'
#' @description
#' \code{load.data.txt} converts text files into a list of data frames.
#'
#' @usage load.data.txt(sampling_ssh.file, reporting_ssh.file)
#'
#' @param sampling_ssh.file Name of the file linking sampling and SSH layers. Each row denotes a sampling unit. At least two columns need to be included in this file: value of the sampling attribute and the stratum each sampling unit falling into.
#' @param reporting_ssh.file Name of the file linking reporting and SSH layers. Each row denotes a reporting unit. The weights of each stratum should be specified in the columns.
#'
#' @name load.data.txt
#' @importFrom utils read.delim
#' @export
#'
#' @examples
#' bc.sampling_ssh.name <- system.file("extdata", "bc_sampling_ssh.csv",
#'                                     package="sandwichr")
#' bc.reporting_ssh.name <- system.file("extdata", "bc_reporting_ssh.csv",
#'                                      package="sandwichr")
#'
#' bc.data <- load.data.txt(sampling_ssh.file=bc.sampling_ssh.name,
#'                          reporting_ssh.file=bc.reporting_ssh.name)
#'
# ---- End of roxygen documentation ----

load.data.txt <- function(sampling_ssh.file, reporting_ssh.file){
  sampling_ssh = read.delim(sampling_ssh.file, sep=",", fileEncoding = "UTF-8")
  reporting_ssh = read.delim(reporting_ssh.file, sep=",", fileEncoding = "UTF-8")
  list(sampling_ssh, reporting_ssh)
}
