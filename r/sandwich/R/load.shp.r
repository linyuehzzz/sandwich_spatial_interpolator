#' @title Load shapefile into \code{sf}
#'
#' @description
#' \code{load.shp} converts a shapefile into a \code{sf} object.
#'
#' @usage load.shp(path, file)
#'
#' @param path Directory of the shapefile.
#' @param file Name of the shapefile, minus extension (.shp).

#' @import sf
#' @name load.shp
#' @export
#
# ---- End of roxygen documentation ----

load.shp <- function(path, file){
  df = read_sf(dsn=path, layer=file)
  df
}
