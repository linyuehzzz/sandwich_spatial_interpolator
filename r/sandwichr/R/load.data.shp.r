#' Load shapefiles into \code{sf}s
#'
#' @description
#' Convert shapefiles into a list of \code{sf} objects.
#'
#' @usage load.data.shp(sampling.file,
#'        ssh.file,
#'        reporting.file)
#'
#' @param sampling.file Path to the sampling layer. The sampling layer should be a point \code{sf} object that contains an attribute to be interpolated.
#' @param ssh.file Path to the SSH layer. The SSH layer should be a polygon \code{sf} object.
#' @param reporting.file Path to the reporting layer. The reporting layer should be a polygon \code{sf} object.
#'
#' @return A list of \code{sf} objects.
#'
#' @import sf tools
#' @export
#'
#' @examples
#' hs.sampling.name <- system.file("extdata", "hs.sampling.shapefile.shp",
#'                                 package="sandwichr")
#' hs.ssh.name <- system.file("extdata", "hs.ssh.shapefile.shp",
#'                            package="sandwichr")
#' hs.reporting.name <- system.file("extdata", "hs.reporting.shapefile.shp",
#'                                  package="sandwichr")
#'
#' hs.data <- load.data.shp(sampling.file=hs.sampling.name,
#'                          ssh.file=hs.ssh.name,
#'                          reporting.file=hs.reporting.name)
#'
#' @name load.data.shp
#'
# ---- End of roxygen documentation ----

load.data.shp <- function(sampling.file, ssh.file, reporting.file){
  sampling.lyr = read_sf(dsn=dirname(sampling.file),
                         layer=file_path_sans_ext(basename(sampling.file)))
  ssh.lyr = read_sf(dsn=dirname(ssh.file),
                    layer=file_path_sans_ext(basename(ssh.file)))
  reporting.lyr = read_sf(dsn=dirname(reporting.file),
                          layer=file_path_sans_ext(basename(reporting.file)))
  list(sampling.lyr, ssh.lyr, reporting.lyr)
}
