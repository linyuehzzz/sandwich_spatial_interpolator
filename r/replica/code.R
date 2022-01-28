####################################################################
###################    4.1 Getting started    ######################
####################################################################

options(warn=-1)

### -----------4.1.1 Installing packages------------------
if(FALSE){
  install.packages("devtools")
  install.packages("sf")
  install.packages("tools")
  install.packages("ggpubr")
  install.packages("dplyr")
}

devtools::install_github(repo="linyuehzzz/sandwich_spatial_interpolator",
                         subdir="r/sandwichr", build_vignettes=FALSE)


### -----------4.1.2 Importing packages------------------
library(sandwichr)
library(sf)
library(tools)
library(ggpubr)
library(dplyr)


## Initializing the generator for pseudo random numbers
set.seed(0)


####################################################################
#####################    4.2 Case study 1    #######################
####################################################################

### -----------4.2.1 Loading data------------------
hs.sampling.name <- system.file("extdata", "hs.sampling.shapefile.shp",
                                package="sandwichr")
hs.ssh.name <- system.file("extdata", "hs.ssh.shapefile.shp",
                           package="sandwichr")
hs.reporting.name <- system.file("extdata", "hs.reporting.shapefile.shp",
                                 package="sandwichr")
hs.sampling.name
hs.ssh.name
hs.reporting.name

hs.data <- load.data.shp(sampling.file=hs.sampling.name,
                         ssh.file=hs.ssh.name,
                         reporting.file=hs.reporting.name)
# Sampling
head(hs.data[[1]])
# SSH
head(hs.data[[2]])
# Reporting
head(hs.data[[3]])


### -----------4.2.2 Selecting SSH layers(s)------------------
# Inputing another candidate SSH layer for demonstration
hs.ssh2.name <- system.file("extdata", "hs.ssh2.shapefile.shp",
                            package="sandwichr")
hs.ssh2 <- read_sf(dsn=dirname(hs.ssh2.name),
                   layer=file_path_sans_ext(basename(hs.ssh2.name)))
head(hs.ssh2)

# Preparing the SSH layer(s) for evaluation
hs.join <- ssh.data.shp(object=hs.data[[1]], ssh.lyr=hs.data[[2]], ssh.id="STR_1")
hs.join <- ssh.data.shp(object=hs.join, ssh.lyr=hs.ssh2, ssh.id="STR_2")
head(hs.join)

# Calculating the geographical detector q-statistic
ssh.test(object=hs.join, y="Population", x=c("STR_1", "STR_2"), test="factor")

# Calculating the interaction detector
ssh.test(object=hs.join, y="Population", x=c("STR_1", "STR_2"), test="interaction")


### -----------4.2.3 Running the Sandwich model------------------
# Perform the SSH based spatial interpolation
hs.sw <- sandwich.model(object=hs.data, sampling.attr="Population", type="shp")
head(hs.sw$object)
summary(hs.sw)

# Calculating the confidence intervals of the interpolation estimates
hs.sw.ci <- sandwich.ci(object=hs.sw, level=.95)
head(hs.sw.ci$object$object)
summary(hs.sw.ci)

# Plotting
ggplot2::autoplot(object=hs.sw)
ggplot2::autoplot(object=hs.sw.ci)


### -----------4.2.4 Model validation------------------
hs.cv <- sandwich.cv(object=hs.data, sampling.attr="Population", k=5, type="shp")
hs.cv


####################################################################
#####################    4.3 Case study 2    #######################
####################################################################

### -----------4.3.1 Loading data------------------
bc.sampling_ssh.name <- system.file("extdata", "bc_sampling_ssh.csv",
                                    package="sandwichr")
bc.reporting_ssh.name <- system.file("extdata", "bc_reporting_ssh.csv",
                                     package="sandwichr")
bc.sampling_ssh.name
bc.reporting_ssh.name

bc.data <- load.data.txt(sampling_ssh.file=bc.sampling_ssh.name,
                         reporting_ssh.file=bc.reporting_ssh.name)

head(bc.data[[1]])    # Sampling-SSH
head(bc.data[[2]])    # Reporting-SSH


### -----------4.3.2 Selecting SSH layers(s)------------------
bc.join <- ssh.data.txt(object=bc.data)
head(bc.join)

# Calculating the geographical detector q-statistic
ssh.test(object=bc.join, y="Incidence", x="SSHID", test="factor", type="txt")

# Visualizing urban-rural disparities
p <- ggerrorplot(bc.data[[1]], x="SSHID", y="Incidence",
                desc_stat="mean_sd", color="black",
                add="violin", add.params=list(color = "darkgray"))

p + scale_x_discrete(labels=c("1"="Urban", "2"="Rural")) +
  theme(axis.title.x=element_blank()) + labs(y="Breast Cancer Incidence\n(Rate per 100,000)")

bc.data[[1]] %>%
  group_by(SSHID) %>%
  summarise_at(vars(Incidence),
               list(name = mean))


### -----------4.3.3 Running the model------------------
# Performing the SSH based spatial interpolation
bc.sw <- sandwich.model(object=bc.data, sampling.attr="Incidence", type="txt",
                        ssh.id.col="SSHID", ssh.weights=list(c(1,2), c("W1","W2")))
head(bc.sw$object)
summary(bc.sw)

# Calculating the confidence intervals of the interpolation estimates
bc.sw.ci <- sandwich.ci(object=bc.sw, level=.95)
head(bc.sw.ci$object$object)
summary(bc.sw.ci)


### -----------4.3.4 Model validation------------------
bc.cv <- sandwich.cv(object=bc.data, sampling.attr="Incidence", k=5, type="txt",
                     ssh.id.col="SSHID", reporting.id.col="GBCODE",
                     ssh.weights=list(c(1,2), c("W1","W2")))
bc.cv


# knitr::spin("code.R")
