####################################################################
###################    4.1 Getting started    ######################
####################################################################

options(warn=-1)

### -----------4.1.1 Installing packages------------------
if(FALSE){
  install.packages("sandwichr")
  install.packages("sf")
  install.packages("tools")
  install.packages("ggpubr")
  install.packages("dplyr")
  install.packages("ggplot2")
  install.packages("ggnewscale")
  install.packages("png")
  install.packages("grid")
}


### -----------4.1.2 Importing packages------------------
library(sandwichr)
library(ggnewscale)
library(ggplot2)
library(sf)
library(tools)
library(ggpubr)
library(dplyr)
library(png)
library(grid)


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
class(hs.data[[1]])
attributes(hs.data[[1]])
summary(hs.data[[1]])

# SSH
head(hs.data[[2]])
class(hs.data[[2]])
attributes(hs.data[[2]])
summary(hs.data[[2]])

# Reporting
head(hs.data[[3]])
class(hs.data[[3]])
attributes(hs.data[[3]])
summary(hs.data[[3]])

# Visualizing data inputs (Figure 5a)
ggplot() +
  geom_sf(data=hs.data[[2]],
          aes(fill=STR),
          fill="#FAFAFA", 
          colour="#B2B2B2") + 
  geom_sf(data=hs.data[[1]], 
          aes(colour=Population)) +
  scale_color_gradient(low="#E5D5F2",
                       high="#5D2C70",
                       breaks=c(100,200,300,400),
                       labels=c("<100","100-199","200-299",">=300"),
                       guide=guide_legend(title="Sampled Human\nPopulation Density\n(Persons Per Square Mile)",
                                          override.aes=list(shape=c(20,20)))) +
  coord_sf(crs=st_crs(4283)) +
  theme_void() +
  theme(
    legend.key.size=unit(0.5,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0.25,0.3),
    legend.spacing.x=unit(0,'cm'),
    legend.title=element_text(face="bold", size=8),
    legend.text=element_text(size=8)
  )
ggsave("outputs/Fig5-1.eps", 
       width=11, 
       height=9, 
       units="cm")

# Visualizing data inputs (Figure 5b)
hs.plot.5b <- hs.data[[3]]
hs.plot.5b$group = c(0,1,0,0,1,0,1,0,0,0)
ggplot() +
  geom_sf(data=hs.plot.5b,
          aes(fill=as.factor(group)),
          colour="#B2B2B2") + 
  scale_fill_manual(values = c("#FAFAFA","gray80"),
                    labels=c("With samples","No samples"),
                    guide=guide_legend(title="Reporting Units")) +
  theme_void() +
  theme(
    legend.key.size=unit(0.5,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0.25,0.3),
    legend.spacing.x=unit(0.1,'cm'),
    legend.title=element_text(face="bold", size=8),
    legend.text=element_text(size=8)
  )
ggsave("outputs/Fig5-2.eps", 
       width=11, 
       height=9, 
       units="cm")


### -----------4.2.2 Selecting SSH layers(s)------------------
# Inputing another candidate SSH layer for demonstration
hs.ssh2.name <- system.file("extdata", "hs.ssh2.shapefile.shp",
                            package="sandwichr")
hs.ssh2 <- read_sf(dsn=dirname(hs.ssh2.name),
                   layer=file_path_sans_ext(basename(hs.ssh2.name)))
head(hs.ssh2)

# Preparing the SSH layer(s) for evaluation
hs.join <- ssh.data.shp(object=hs.data[[1]], 
                        ssh.lyr=hs.data[[2]], 
                        ssh.id="STR_1")
hs.join <- ssh.data.shp(object=hs.join, 
                        ssh.lyr=hs.ssh2, 
                        ssh.id="STR_2")
head(hs.join)

# Calculating the geographical detector q-statistic
ssh.test(object=hs.join, 
         y="Population", 
         x=c("STR_1", "STR_2"), 
         test="factor")

# Calculating the interaction detector
ssh.test(object=hs.join, 
         y="Population", 
         x=c("STR_1", "STR_2"), 
         test="interaction")


### -----------4.2.3 Running the Sandwich model------------------
# Perform the SSH based spatial interpolation
hs.sw <- sandwich.model(object=hs.data, 
                        sampling.attr="Population", 
                        type="shp")
head(hs.sw$object)
summary(hs.sw)

sf::st_write(obj=hs.sw$object, 
             dsn="outputs/hs.sw.shp")

# Calculating the confidence intervals of the interpolation estimates
hs.sw.ci <- sandwich.ci(object=hs.sw, 
                        level=.95)
head(hs.sw.ci$object$object)
summary(hs.sw.ci)

sf::st_write(obj=hs.sw.ci$object$object, 
             dsn="outputs/hs.sw.ci.shp")

# Plotting (Figures 6 and 7)
ggplot2::autoplot(object=hs.sw)
ggplot2::autoplot(object=hs.sw.ci)


### -----------4.2.4 Model validation------------------
hs.cv <- sandwich.cv(object=hs.data, 
                     sampling.attr="Population", 
                     k=5, 
                     type="shp")
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

# Sampling-SSH
head(bc.data[[1]])    
class(bc.data[[1]])
summary(bc.data[[1]])

# Reporting-SSH
head(bc.data[[2]])    
class(bc.data[[2]])
summary(bc.data[[2]])


### -----------4.3.2 Selecting SSH layers(s)------------------
bc.join <- ssh.data.txt(object=bc.data)
head(bc.join)

# Calculating the geographical detector q-statistic
ssh.test(object=bc.join, 
         y="Incidence", 
         x="SSHID", 
         test="factor", 
         type="txt")

# Visualizing data inputs (Figure 8a)
province <- read_sf("res/province.shp")
rivers <- read_sf("res/rivers.shp")
img <- readPNG("res/southsea.png")
g <- rasterGrob(img, interpolate=TRUE)
bc.dat1 <- bc.data[[1]] %>% filter(SSHID==1) # urban
bc.dat2 <- bc.data[[1]] %>% filter(SSHID==2) # rural

#+ echo=FALSE, fig.width=10
ggplot() + 
  annotation_custom(g, xmin = 125, xmax = 133, 
                    ymin = 15, ymax = 26) +
  geom_sf(data=province,
          fill="#FAFAFA",
          colour="#B2B2B2") +
  geom_sf(data=rivers, 
          colour="#7AB6F5") +
  geom_point(data=bc.dat1, 
             aes(x=X, y=Y, colour=Incidence)) +
  scale_color_gradient(low="#DCF5E9",
                       high="#226633",
                       limits = c(0,65),
                       breaks=c(15,30,45,60),
                       labels=c("","","",""),
                       guide=guide_legend(title="Urban",
                                          override.aes=list(shape=c(20,20)))) +
  new_scale_color() +
  geom_point(data=bc.dat2, 
             aes(x=X, y=Y, colour=Incidence)) +
  scale_color_gradient(low="#E5D5F2",
                       high="#5D2C70",
                       limits = c(0,65),
                       breaks=c(15,30,45,60),
                       labels=c("<15","15-29","30-44",">=45"),
                       guide=guide_legend(title="Rural",
                                          override.aes=list(shape=c(20,20)))) +
  coord_sf(xlim=c(72, 135), ylim=c(14.1, 55.5)) +
  labs(title="Sampled Breast Cancer Incidence\n(Rate Per 100,000)") +
  theme_void() +
  theme(
    plot.title=element_text(vjust=-20, hjust=0.5, size=8, face="bold"),
    legend.key.size=unit(0.5,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0.17,0.3),
    legend.spacing.x=unit(0,'cm'),
    legend.spacing.y=unit(0,'cm'),
    legend.title=element_text(face="bold", size=8),
    legend.text=element_text(size=8),
    legend.box="horizontal"
  ) 
ggsave("outputs/Fig8-1.pdf", 
       width=10, 
       height=9, 
       units="cm")

# Visualizing urban-rural disparities (Figure 8b)
means <- aggregate(Incidence ~ SSHID, 
                   bc.data[[1]], 
                   mean)

#+ echo=FALSE, fig.width=10
ggerrorplot(bc.data[[1]], 
            x="SSHID", 
            y="Incidence",
            desc_stat="mean_sd", 
            color="black",
            add="violin", 
            add.params=list(color="darkgray"),
            ylab="Breast Cancer Incidence\n(Rate per 100,000)") + 
  scale_x_discrete(labels=c("1"="Urban", "2"="Rural")) +
  theme(axis.title=element_text(face="bold", size=10),
        axis.text.x=element_text(size=10),
        axis.title.x=element_blank()) + 
  geom_text(data=means, 
            aes(label=format(Incidence,digits=3), 
                hjust=-0.3)) + 
  guides(fill=guide_legend(ncol=2))

bc.data[[1]] %>%
  group_by(SSHID) %>%
  summarise_at(vars(Incidence),
               list(name = mean))

# Visualizing urbanization rate (Figure 9)
#+ echo=FALSE, fig.width=10
county <- read_sf("res/county.shp")
ggplot() + 
  annotation_custom(g, xmin = 125, xmax = 133, 
                    ymin = 15, ymax = 26) +
  geom_sf(data=county, aes(fill=URBAN_RATE), colour=NA) +
  geom_sf(data=province,
          fill=NA,
          colour="white") +
  geom_sf(data=rivers, 
          colour="#7AB6F5") +
  scale_fill_gradient(low="#CCCCFF",
                      high="#0000E0",
                      guide=guide_colorbar(title="Urbanization Rate")) +
  coord_sf(xlim=c(72, 135), ylim=c(14.1, 55.5)) +
  theme_void() +
  theme(
    legend.key.height=unit(0.35,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0,0.2),
    legend.title=element_text(face="bold", size=6),
    legend.text=element_text(size=6),
    legend.direction='horizontal'
  ) 
ggsave("outputs/Fig9.pdf", 
       width=10, 
       height=9, 
       units="cm")


### -----------4.3.3 Running the model------------------
# Performing the SSH based spatial interpolation
bc.sw <- sandwich.model(object=bc.data, 
                        sampling.attr="Incidence", 
                        type="txt",
                        ssh.id.col="SSHID", 
                        ssh.weights=list(c(1,2), c("W1","W2")))
head(bc.sw$object)
summary(bc.sw)

write.csv(x=bc.sw$object, 
          file="outputs/bc.sw.csv")

# Calculating the confidence intervals of the interpolation estimates
bc.sw.ci <- sandwich.ci(object=bc.sw, 
                        level=.95)
head(bc.sw.ci$object$object)
summary(bc.sw.ci)

write.csv(x=bc.sw.ci$object$object, 
          file="outputs/bc.sw.ci.csv")

# Linking and visualizing
bc.plot <- county %>% 
  left_join(bc.sw.ci$object$object)

# Mean
ggplot() +
  annotation_custom(g, xmin = 125, xmax = 133, 
                    ymin = 15, ymax = 26) +
  geom_sf(data=bc.plot,
          aes(fill=mean), 
          colour=NA) +
  geom_sf(data=province,
          fill=NA,
          colour="white") +
  geom_sf(data=rivers, 
          colour="#7AB6F5") +
  scale_fill_gradient(low="white",
                      high="red",
                      breaks=c(20,24,28),
                      guide=guide_colorbar(title="Mean")) +
  coord_sf(xlim=c(72, 135), ylim=c(14.1, 55.5)) +
  theme_void() +
  theme(
    legend.key.height=unit(0.35,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0,0.2),
    legend.title=element_text(face="bold", size=6),
    legend.text=element_text(size=6),
    legend.direction='horizontal'
  ) 
ggsave("outputs/Fig10_1.pdf", 
       width=10, 
       height=9, 
       units="cm")

# SE  
ggplot() +
  annotation_custom(g, xmin = 125, xmax = 133, 
                    ymin = 15, ymax = 26) +
  geom_sf(data=bc.plot,
          aes(fill=se), 
          colour=NA) +
  geom_sf(data=province,
          fill=NA,
          colour="white") +
  geom_sf(data=rivers, 
          colour="#7AB6F5") +
  scale_fill_gradient(low="white",
                      high="blue",
                      guide=guide_colorbar(title="Standard Error")) +
  coord_sf(xlim=c(72, 135), ylim=c(14.1, 55.5)) +
  theme_void() +
  theme(
    legend.key.height=unit(0.35,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0,0.2),
    legend.title=element_text(face="bold", size=6),
    legend.text=element_text(size=6),
    legend.direction='horizontal'
  )
ggsave("outputs/Fig10_2.pdf", 
       width=10, 
       height=9, 
       units="cm")

# CI
ggplot() +
  annotation_custom(g, xmin = 125, xmax = 133, 
                    ymin = 15, ymax = 26) +
  geom_sf(data=bc.plot,
          aes(fill=ci.low), 
          colour=NA) +
  geom_sf(data=province,
          fill=NA,
          colour="white") +
  geom_sf(data=rivers, 
          colour="#7AB6F5") +
  scale_fill_gradient(low="white",
                      high="red",
                      breaks=c(20,24,28),
                      guide=guide_colorbar(title="Confidence Interval\n(Lower Bound)")) +
  coord_sf(xlim=c(72, 135), ylim=c(14.1, 55.5)) +
  theme_void() +
  theme(
    legend.key.height=unit(0.35,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0,0.2),
    legend.title=element_text(face="bold", size=6),
    legend.text=element_text(size=6),
    legend.direction='horizontal'
  )
ggsave("outputs/Fig10_3.pdf", 
       width=10, 
       height=9, 
       units="cm")

ggplot() +
  annotation_custom(g, xmin = 125, xmax = 133, 
                    ymin = 15, ymax = 26) +
  geom_sf(data=bc.plot,
          aes(fill=ci.up), 
          colour=NA) +
  geom_sf(data=province,
          fill=NA,
          colour="white") +
  geom_sf(data=rivers, 
          colour="#7AB6F5") +
  scale_fill_gradient(low="white",
                      high="red",
                      breaks=c(20,24,28),
                      guide=guide_colorbar(title="Confidence Interval\n(Upper Bound)")) +
  coord_sf(xlim=c(72, 135), ylim=c(14.1, 55.5)) +
  theme_void() +
  theme(
    legend.key.height=unit(0.35,'cm'),
    legend.justification=c(0,1),
    legend.position=c(0,0.2),
    legend.title=element_text(face="bold", size=6),
    legend.text=element_text(size=6),
    legend.direction='horizontal'
  )
ggsave("outputs/Fig10_4.pdf", 
       width=10, 
       height=9, 
       units="cm")


### -----------4.3.4 Model validation------------------
bc.cv <- sandwich.cv(object=bc.data, 
                     sampling.attr="Incidence", 
                     k=5, 
                     type="txt",
                     ssh.id.col="SSHID", 
                     reporting.id.col="GBCODE",
                     ssh.weights=list(c(1,2), c("W1","W2")))
bc.cv


# knitr::spin("code.R")
