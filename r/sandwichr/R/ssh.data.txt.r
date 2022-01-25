#' @title Prepare text data for Geodetector
#'
#' @description
#' \code{ssh.data.txt} prepare the input from text files for the geographical detector model.
#'
#' @usage ssh.data.txt(object)
#'
#' @param object A list of 2 data frames generated by \code{load.data.txt}, including a file linking sampling and SSH layers linking reporting and SSH layers and a file.
#'
#' @seealso [https://cran.r-project.org/package=geodetector]{geodetector R package}
#' @import sf dplyr
#' @name ssh.data.txt
#' @export
#'
#' @examples
#' data(bc.data)
#' bc.join <- ssh.data.txt(object=bc.data)
# ---- End of roxygen documentation ----

ssh.data.txt <- function(object){

  object[[1]]
}
