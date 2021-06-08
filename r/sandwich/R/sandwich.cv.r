#' @title Perform \emph{k}-fold cross validation
#'
#' @description
#' \code{sandwich.cv} perfoms \emph{k}-fold cross validation to evaluate the overall model accuracy and outputs the average root mean square error (RMSE).
#'
#' @usage sandwich.cv(sampling.lyr, ssh.lyr, reporting.lyr, sampling.attr, k=10)
#'
#' @param sampling.lyr A POINT \code{sf} object used as the sampling layer. It should contain an attribute that is to be interpolated.
#' @param ssh.lyr A POLYGON \code{sf} object used as the SSH layer.
#' @param reporting.lyr A POLYGON \code{sf} object used as the reporting layer.
#' @param sampling.attr A \code{string} denoting the name of the attribute in the sampling layer to be interpolated.
#' @param k The number of folds (\code{k} > 1). By default, \code{k} = 10.
#'
#' @import sf, caret
#' @importFrom st_geometry, st_geometry_type, is.element, st_join
#' @name sandwich.cv
#' @export
#
# ---- End of roxygen documentation ----


sandwich.cv <- function(sampling.lyr, ssh.lyr, reporting.lyr, sampling.attr, k=10){

  #--------------------------- Check inputs ----------------------------------
  if (st_geometry_type(sampling.lyr, by_geometry=FALSE) != "POINT"){
    stop("Geometry type of the sampling layer should be POINT.")
  }
  if (st_geometry_type(ssh.lyr, by_geometry=FALSE) != "POLYGON"){
    stop("Geometry type of the SSH layer should be POLYGON.")
  }
  if (st_geometry_type(reporting.lyr, by_geometry=FALSE) != "POLYGON"){
    stop("Geometry type of the reporting layer should be POLYGON.")
  }
  if (!is.element(sampling.attr, names(sampling.lyr))){
    stop("Attribute name not found in the sampling layer.")
  }

  #----------------------- Create k equally-sized folds ------------------------
  sampling.lyr$index = 1:nrow(sampling.lyr)
  folds = createFolds(sampling.lyr$index, k=k)

  #----------------------- k-fold cross validation ------------------------
  rmse = 0
  for(i in 1:k){
    # split data sets
    val = lapply(folds[i], function(ind, dat) dat[ind,], dat=sampling.lyr)
    val = st_as_sf(as.data.frame(val))
    dev = lapply(list(unique(unlist(folds[-i]))), function(ind, dat) dat[ind,], dat=sampling.lyr)
    dev = st_as_sf(as.data.frame(dev))
    # perform sandwich model
    out = sandwich.model(dev, ssh.lyr, reporting.lyr, sampling.attr)
    # calculate MSE
    val.join = st_join(val, out)
    st_geometry(val.join) = NULL
    val.join = as.data.frame(val.join)
    new.attr.name = paste(names(folds)[i], sampling.attr, sep=".")
    dif = (val.join[new.attr.name] - val.join$mean)[[new.attr.name]]
    rmse[i] = sqrt(mean(dif^2))
  }
  rmse.mean = mean(rmse)
  rmse.mean
}
