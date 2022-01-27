## ----setup, include = FALSE---------------------------------------------------
knitr::opts_chunk$set(echo = TRUE, warning=FALSE, message=FALSE, fig.cap = " ", fig.path='figs/')

## -----------------------------------------------------------------------------
# Install the sandwichr package
# require("devtools")
# devtools::install_github("linyuehzzz/sandwich_spatial_interpolator", 
#                          subdir="r/sandwichr", build_vignettes = TRUE)

## -----------------------------------------------------------------------------
# Import the sandwichr package and other packages
library("sandwichr")
library(ggplot2)
library(ggpubr)
library(dplyr)

## -----------------------------------------------------------------------------
# Input data from shapefiles
hs.sampling.name <- system.file("extdata", "hs.sampling.shapefile.shp", 
                                package="sandwichr")
hs.ssh.name <- system.file("extdata", "hs.ssh.shapefile.shp", 
                           package="sandwichr")
hs.reporting.name <- system.file("extdata", "hs.reporting.shapefile.shp", 
                                 package="sandwichr")

hs.data <- load.data.shp(sampling.file=hs.sampling.name, 
                      ssh.file=hs.ssh.name,
                      reporting.file=hs.reporting.name)

## -----------------------------------------------------------------------------
library(sf)
library(tools)
# Input another candidate SSH layer for demonstration
hs.ssh2.name <- system.file("extdata", "hs.ssh2.shapefile.shp", 
                            package="sandwichr")
hs.ssh2 <- read_sf(dsn=dirname(hs.ssh2.name),
                    layer=file_path_sans_ext(basename(hs.ssh2.name)))

## -----------------------------------------------------------------------------
# Prepare the SSH layer(s) for evaluation
hs.join <- ssh.data.shp(object=hs.data[[1]], ssh.lyr=hs.data[[2]], ssh.id="STR_1")
hs.join <- ssh.data.shp(object=hs.join, ssh.lyr=hs.ssh2, ssh.id="STR_2")
head(hs.join)

## -----------------------------------------------------------------------------
# Calculate the geographical detector q-statistic
ssh.test(object=hs.join, y="Population", x=c("STR_1", "STR_2"), test="factor")

## -----------------------------------------------------------------------------
# Calculate the interaction detector
ssh.test(object=hs.join, y="Population", x=c("STR_1", "STR_2"), test="interaction")

## -----------------------------------------------------------------------------
# Perform the SSH based spatial interpolation
hs.sw <- sandwich.model(object=hs.data, sampling.attr="Population", type="shp")
head(hs.sw$object)

## ----fig.align="center", fig.width=4, fig.height=3----------------------------
# Plot the estimated mean values and standard errors
ggplot2::autoplot(object=hs.sw)

## -----------------------------------------------------------------------------
# Calculate the confidence intervals of the interpolation estimates
hs.sw.ci <- sandwich.ci(object=hs.sw, level=.95)
head(hs.sw.ci$object$object)

## ----fig.align="center", fig.width=8, fig.height=3----------------------------
# Plot the confidence intervals of the interpolation estimates
ggplot2::autoplot(object=hs.sw.ci)

## -----------------------------------------------------------------------------
# Perform k-fold cross validation
set.seed(0)
hs.cv <- sandwich.cv(object=hs.data, sampling.attr="Population", k=5, type="shp")
hs.cv

## -----------------------------------------------------------------------------
# Input data from text files
bc.sampling_ssh.name <- system.file("extdata", "bc_sampling_ssh.csv", 
                                package="sandwichr")
bc.reporting_ssh.name <- system.file("extdata", "bc_reporting_ssh.csv", 
                                 package="sandwichr")

bc.data <- load.data.txt(sampling_ssh.file=bc.sampling_ssh.name, 
                         reporting_ssh.file=bc.reporting_ssh.name)

# Sampling-SSH
head(bc.data[[1]])

# Reporting-SSH
head(bc.data[[2]])

## -----------------------------------------------------------------------------
# Prepare the SSH layer for evaluation
bc.join <- ssh.data.txt(object=bc.data)
head(bc.join)

## -----------------------------------------------------------------------------
# Calculate the geographical detector q-statistic
ssh.test(object=bc.join, y="Incidence", x="SSHID", test="factor", type="txt")

## -----------------------------------------------------------------------------
p = ggerrorplot(bc.data[[1]], x = "SSHID", y = "Incidence", 
            desc_stat = "mean_sd", color = "black",
            add = "violin", add.params = list(color = "darkgray")
            )

p + scale_x_discrete(labels=c("1" = "Urban", "2" = "Rural")) + 
  theme(axis.title.x = element_blank()) + labs(y="Breast Cancer Incidence (Rate per 100,000)")

bc.data[[1]] %>%                                        
  group_by(SSHID) %>%                         
  summarise_at(vars(Incidence),              
               list(name = mean))               

## -----------------------------------------------------------------------------
# Perform the SSH based spatial interpolation
bc.sw <- sandwich.model(object=bc.data, sampling.attr="Incidence", type="txt", 
                        ssh.id.col="SSHID", ssh.weights=list(c(1,2), c("W1","W2")))
head(bc.sw$object)

## -----------------------------------------------------------------------------
# Calculate the confidence intervals of the interpolation estimates
bc.sw.ci <- sandwich.ci(object=bc.sw, level=.95)
head(bc.sw.ci$object$object)

## -----------------------------------------------------------------------------
# Perform k-fold cross validation
set.seed(0)
bc.cv <- sandwich.cv(object=bc.data, sampling.attr="Incidence", k=5, type="txt", 
                     ssh.id.col="SSHID", reporting.id.col="GBCODE", 
                     ssh.weights=list(c(1,2), c("W1","W2")))
bc.cv

