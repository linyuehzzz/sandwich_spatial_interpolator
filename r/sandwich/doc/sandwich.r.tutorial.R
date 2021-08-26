## ----setup, include = FALSE---------------------------------------------------
knitr::opts_chunk$set(echo = TRUE, warning=FALSE, message=FALSE, fig.cap = " ", fig.path='figs/')

## -----------------------------------------------------------------------------
# Install sandwich package
# install.packages("Sandwich")
# Import sandwich package
library("Sandwich")

## -----------------------------------------------------------------------------
# Input data from shapefiles
hs.data <- load.data.shp(path="./data", sampling.file="hs.sampling.shapefile", 
                         ssh.file="hs.ssh.shapefile", reporting.file="hs.reporting.shapefile")

## -----------------------------------------------------------------------------
# Input another candidate SSH layer for demonstration
hs.ssh2 <- read_sf(dsn="./data", layer="hs.ssh2.shapefile")

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
head(hs.sw)

## ----fig.align="center", fig.width=4, fig.height=3----------------------------
# Plot the mean values of the interpolation estimates
plot.mean(object=hs.sw)
# Plot the standard errors of the interpolation estimates
plot.se(object=hs.sw)

## -----------------------------------------------------------------------------
# Calculate the confidence intervals of the interpolation estimates
hs.sw.ci <- sandwich.ci(object=hs.sw, level=.95)
head(hs.sw.ci)

## ----fig.align="center", fig.width=8, fig.height=3----------------------------
# Plot the confidence intervals of the interpolation estimates
plot.ci(object=hs.sw.ci)

## -----------------------------------------------------------------------------
# Perform k-fold cross validation
hs.cv <- sandwich.cv(object=hs.data, sampling.attr="Population", k=5, type="shp")
hs.cv

## -----------------------------------------------------------------------------
# Input data from text files
bc.data <- load.data.txt(sampling_ssh.file="./data/bc_sampling_ssh.csv", 
                         reporting_ssh.file="./data/bc_reporting_ssh.csv")

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
library(ggpubr)
library(dplyr)   
p = ggerrorplot(bc.data[[1]], x = "SSHID", y = "Incidence", 
            desc_stat = "mean_sd", color = "black",
            add = "violin", add.params = list(color = "darkgray")
            )

p + scale_x_discrete(labels=c("1" = "Urban", "2" = "Rural")) + 
  theme(axis.title.x = element_blank())

bc.data[[1]] %>%                                        
  group_by(SSHID) %>%                         
  summarise_at(vars(Incidence),              
               list(name = mean))               

## -----------------------------------------------------------------------------
# Perform the SSH based spatial interpolation
bc.sw <- sandwich.model(object=bc.data, sampling.attr="Incidence", type="txt", 
                        ssh.id.col="SSHID", ssh.weights=list(c(1,2), c("W1","W2")))
head(bc.sw)

## -----------------------------------------------------------------------------
# Calculate the confidence intervals of the interpolation estimates
bc.sw.ci <- sandwich.ci(object=bc.sw, level=.95)
head(bc.sw.ci)

## -----------------------------------------------------------------------------
# Perform k-fold cross validation
bc.cv <- sandwich.cv(object=bc.data, sampling.attr="Incidence", k=5, type="txt", 
                     ssh.id.col="SSHID", reporting.id.col="GBCODE", 
                     ssh.weights=list(c(1,2), c("W1","W2")))
bc.cv

