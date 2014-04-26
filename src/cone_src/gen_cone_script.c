#include<stdio.h>

main(int argc, char *argv[])
{
    int g, min_g, max_g;
    FILE *outfile;
    char outfile_name[] = "cone_script";
    char b[100];
    char conetypeplaceholder[100];
    char *conetype;

    if (argc < 2)
    {
	printf("Enter cone type (flag, mg, or flag2mg) : ");
	scanf("%s", conetypeplaceholder);
	conetype = conetypeplaceholder;
    }
    else
	conetype = argv[1];
    
    if (argc < 3)
    {
	printf("Enter starting genus : ");
	scanf("%d", &min_g);
    }
    else
	min_g = atoi(argv[2]);
    
    if (argc < 4)
    {
	printf("Enter ending genus : ");
	scanf("%d", &max_g);
    }
    else
	max_g = atoi(argv[3]);

    outfile = fopen(outfile_name, "w");

    fprintf(outfile, "cd cones\n");

    for (g = min_g ; g <= max_g ; g++){
	fprintf(outfile, "echo 'generating the %s cone for genus %d ...'\n", 
		conetype, g);
	fprintf(outfile, "bin/gen_%s_cone_raw %d > %s_extremal-%d\n",
		conetype, g, conetype, g);
	fprintf(outfile, "echo 'done.'\n");
	fprintf(outfile, "echo 'The data for the %s cone for genus %d has ",
		conetype, g);
	fprintf(outfile, "been placed in the file:'\n");

	fprintf(outfile, "echo 'cones/%s_extremal-%d'\n", conetype, g);
    }
}
