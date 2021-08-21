#' @title Load shapefiles into \code{sf}s
#'
#' @description
#' \code{load.data.shp} converts shapefiles into a list of \code{sf} objects.
#'
#' @usage load.data.shp(path, sampling.file, ssh.file, reporting.file)
#'
#' @param path Directory of the shapefile.
#' @param sampling.file Name of the sampling layer, minus extension (.shp). The sampling layer should be a point feature that contains an attribute that is to be interpolated.
#' @param ssh.file Name of the SSH layer, minus extension (.shp). The SSH layer should be a polygon feature.
#' @param reporting.file Name of the reporting layer, minus extension (.shp). The reporting layer should be a polygon feature.
#'
#' @import sf
#' @name load.data.shp
#' @export
#
# ---- End of roxygen documentation ----

load.data.shp <- function(path, sampling.file, ssh.file, reporting.file){
  sampling.lyr = read_sf(dsn=path, layer=sampling.file)
  ssh.lyr = read_sf(dsn=path, layer=ssh.file)
  reporting.lyr = read_sf(dsn=path, layer=reporting.file)
  list(sampling.lyr, ssh.lyr, reporting.lyr)
}
