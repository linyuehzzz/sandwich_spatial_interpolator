#' @title Prepare shapefile data for Geodetector
#'
#' @description
#' \code{ssh.data.shp} joins a candidate SSH layer to an existing layer.
#'
#' @usage ssh.data.shp(object, ssh.lyr, ssh.id, ssh.name=NULL)
#'
#' @param object A POINT \code{sf} object to be joint. Its geometry should be consistent with the sampling layer, but it may have additional attributes from the SSH layer(s).
#' @param ssh.lyr A POLYGON \code{sf} object used as the candidate SSH layer. Its strata ID will be linked to \code{object}.
#' @param ssh.id A \code{string} denoting the attribute name of strata ID in the SSH layer.
#' @param ssh.name A \code{string} denoting the new attribute name assigned to the strata ID in the output object. If \code{NULL}, the attribute name will be the same as that in the old SSH layer.
#'
#' @seealso \link[https://cran.r-project.org/package=geodetector]{geodetector R package}
#' @import sf dplyr
#' @name ssh.data.shp
#' @export
#'
#' @examples
#' library(sf)
#' library(tools)
#' data(hs.data)
#' hs.ssh2.name <- system.file("extdata", "hs.ssh2.shapefile.shp",
#'                             package="sandwichr")
#' hs.ssh2 <- read_sf(dsn=dirname(hs.ssh2.name),
#'                   layer=file_path_sans_ext(basename(hs.ssh2.name)))
#' hs.join <- ssh.data.shp(object=hs.data[[1]], ssh.lyr=hs.data[[2]], ssh.id="STR_1")
#' hs.join <- ssh.data.shp(object=hs.join, ssh.lyr=hs.ssh2, ssh.id="STR_2")
#'
# ---- End of roxygen documentation ----

ssh.data.shp <- function(object, ssh.lyr, ssh.id, ssh.name=NULL){

  #--------------------------- Check inputs ----------------------------------
  if (st_geometry_type(object, by_geometry=FALSE) != "POINT"){
    stop("Geometry type of the joined layer should be POINT.")
  }
  if (st_geometry_type(ssh.lyr, by_geometry=FALSE) != "POLYGON" &
      st_geometry_type(ssh.lyr, by_geometry=FALSE) != "MULTIPOLYGON"){
    stop("Geometry type of the SSH layer should be POLYGON or MULTIPOLYGON.")
  }
  if (!is.element(ssh.id, names(ssh.lyr))){
    stop("Attribute name not found in the SSH layer.")
  }

  #---------------- Recombining the data ----------------------
  ssh.clean = ssh.lyr %>%
    select(ssh.id, "geometry")
  if (!is.null(ssh.name)){
    names(ssh.clean)[ssh.id] = ssh.name
  }
  join = st_join(object, ssh.clean)
  join
}
