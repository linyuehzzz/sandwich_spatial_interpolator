#' @title Load text files into data frames
#'
#' @description
#' \code{load.data.txt} converts text files into a list of data frames.
#'
#' @usage load.data.txt(path, sampling_ssh.file, reporting_ssh.file)
#'
#' @param path Directory of the shapefile.
#' @param sampling_ssh.file Name of the file linking sampling and SSH layers. Each row denotes a sampling unit. Two columns need to be included in this file: value of the sampling attribute and the stratum each sampling unit falling into.
#' @param reporting_ssh.file Name of the file linking reporting and SSH layers. Each row denotes a reporting unit. The weight $W_{rh}$ should be specified in each column.
#'
#' @import sf
#' @name load.data.txt
#' @export
#
# ---- End of roxygen documentation ----

load.data.txt <- function(sampling_ssh.file, reporting_ssh.file){
  sampling_ssh = read.delim(sampling_ssh.file, sep=",", fileEncoding = "UTF-8-BOM")
  reporting_ssh = read.delim(reporting_ssh.file, sep=",", fileEncoding = "UTF-8-BOM")
  list(sampling_ssh, reporting_ssh)
}
