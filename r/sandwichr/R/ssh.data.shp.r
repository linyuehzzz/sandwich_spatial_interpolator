#' Prepare shapefile data for Geodetector
#'
#' @description
#' Join a candidate SSH layer to an existing layer for the geographical detector model.
#'
#' @usage ssh.data.shp(object,
#'        ssh.lyr,
#'        ssh.id,
#'        ssh.name=NULL)
#'
#' @param object A point \code{sf} object to be joint. Its geometry should be consistent with the sampling layer, but it may have additional attributes from the SSH layer(s).
#' @param ssh.lyr A polygon \code{sf} object used as the candidate SSH layer. Its stratum ID will be linked to \code{object}.
#' @param ssh.id Text for the field name of stratum ID in the SSH layer.
#' @param ssh.name Text for the new field name assigned to the stratum ID in the output object. If \code{NULL}, the attribute name will be the same as that in the old SSH layer.
#' @return An \code{sf} object with the sampling units and the Strata they fall into.
#'
#' @import sf dplyr
#' @export
#'
#' @examples
#' library(sf)
#' library(tools)
#' data(sim.data)
#' sim.join <- ssh.data.shp(object=sim.data[[1]], ssh.lyr=sim.data[[2]], ssh.id="X")
#' head(sim.join)
#'
#' @name ssh.data.shp
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
