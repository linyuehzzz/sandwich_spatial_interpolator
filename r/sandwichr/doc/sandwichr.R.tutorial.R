## ----setup, include = FALSE---------------------------------------------------
knitr::opts_chunk$set(echo = TRUE, warning=FALSE, message=FALSE, fig.cap = " ", fig.path='figs/')

## -----------------------------------------------------------------------------
# Install the sandwichr package
# install.packages("sandwichr")

## -----------------------------------------------------------------------------
# Import the sandwichr package and other packages
library("sandwichr")
library(ggplot2)
library(ggpubr)
library(dplyr)
library(ape)

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

# Sampling
head(hs.data[[1]])
class(hs.data[[1]])
attributes(hs.data[[1]])

# SSH
head(hs.data[[2]])
class(hs.data[[2]])
attributes(hs.data[[2]])

# Reporting
head(hs.data[[3]])
class(hs.data[[3]])
attributes(hs.data[[3]])

## -----------------------------------------------------------------------------
hs.dists <- as.matrix(dist(cbind(hs.data[[1]]$x, hs.data[[1]]$y)))
hs.dists.inv <- 1/hs.dists
diag(hs.dists.inv) <- 0
Moran.I(hs.data[[1]]$Population, hs.dists.inv)

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
summary(hs.sw)

## ----fig.align="center", fig.width=8, fig.height=3----------------------------
# Plot the estimated mean values and standard errors
ggplot2::autoplot(object=hs.sw)

## -----------------------------------------------------------------------------
qqnorm(hs.data[[1]]$Population, pch=1, frame=FALSE)
qqline(hs.data[[1]]$Population, col="steelblue", lwd=2)

## -----------------------------------------------------------------------------
# Calculate the confidence intervals of the interpolation estimates
hs.sw.ci <- sandwich.ci(object=hs.sw, level=.95)
head(hs.sw.ci$object$object)
summary(hs.sw.ci)

## ----fig.align="center", fig.width=8, fig.height=3----------------------------
# Plot the confidence intervals of the interpolation estimates
ggplot2::autoplot(object=hs.sw.ci)

## -----------------------------------------------------------------------------
# Perform k-fold cross validation
set.seed(0)
hs.cv <- sandwich.cv(object=hs.data, sampling.attr="Population", k=5, type="shp", ssh.id.col="STR_1")
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
class(bc.data[[1]])

# Reporting-SSH
head(bc.data[[2]])    
class(bc.data[[2]])

## -----------------------------------------------------------------------------
bc.dists <- as.matrix(dist(cbind(bc.data[[1]]$X, bc.data[[1]]$Y)))
bc.dists.inv <- 1/bc.dists
diag(bc.dists.inv) <- 0
Moran.I(bc.data[[1]]$Incidence, bc.dists.inv)

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

bc.data[[1]] %>%
  group_by(SSHID) %>%
  summarise(mean=mean(Incidence), sd=sd(Incidence), n=n())

## -----------------------------------------------------------------------------
# Perform the SSH based spatial interpolation
bc.sw <- sandwich.model(object=bc.data, sampling.attr="Incidence", type="txt", 
                        ssh.id.col="SSHID", ssh.weights=list(c(1,2), c("W1","W2")))
head(bc.sw$object)
summary(bc.sw)

## -----------------------------------------------------------------------------
qqnorm(bc.data[[1]]$Incidence, pch=1, frame=FALSE)
qqline(bc.data[[1]]$Incidence, col="steelblue", lwd=2)

## -----------------------------------------------------------------------------
# Calculate the confidence intervals of the interpolation estimates
bc.sw.ci <- sandwich.ci(object=bc.sw, level=.95)
head(bc.sw.ci$object$object)
summary(bc.sw.ci)

## -----------------------------------------------------------------------------
# Perform k-fold cross validation
set.seed(0)
bc.cv <- sandwich.cv(object=bc.data, sampling.attr="Incidence", k=5, type="txt", 
                     ssh.id.col="SSHID", reporting.id.col="GBCODE", 
                     ssh.weights=list(c(1,2), c("W1","W2")))
bc.cv

