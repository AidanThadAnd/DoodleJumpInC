# 1 "renderer.c" 1
# 1 "./MODEL.H" 1
# 1 "./TYPES.H" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 78 "./MODEL.H" 2




typedef struct
{
    UINT16 prev_x_one, prev_y_one;
    UINT16 prev_x_two, prev_y_two;
    UINT16 prev_x_three, prev_y_three;
    UINT16 x, y;
    UINT16 facing;
    UINT16 prev_facing;
} Doodle;

typedef struct
{
    UINT16 prev_x, prev_y;
    UINT16 x, y;
} Monster;

typedef struct
{
    UINT16 prev_x, prev_y;
    UINT16 x, y;
} Platform;

typedef struct {
    Doodle doodle;
    Monster monster;
    Platform platforms[15 ];
} Model;

void initialize_model(Model *model);

void move_doodle(Doodle *doodle, UINT16 displacement_x, UINT16 displacement_y, UINT16 newFacing);
void move_monster(Monster *monster, UINT16 displacement_x, UINT16 displacement_y);
void move_platform_relative(Platform *platform, UINT16 displacement_x, UINT16 displacement_y, UINT8 selected_platform);
void move_platform_absolute(Platform *platforms, UINT16 x, UINT16 y, UINT8 selected_platform);

UINT8 has_doodle_moved(Doodle *doodle);
UINT8 has_monster_moved(Monster *monster);
UINT8 has_platform_moved(Platform *platform);
# 1 "renderer.c" 2
# 1 "./RASTER.H" 1
# 1 "./types.h" 1
# 107 "./RASTER.H" 2
# 1 "./system.h" 1
# 108 "./RASTER.H" 2


void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_screen(UINT8 *base);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
# 2 "renderer.c" 2
# 1 "./BITMAP.H" 1
# 1 "./types.h" 1
# 4 "./BITMAP.H" 2
# 18 "./BITMAP.H"
extern const UINT32 doodle_bitmap_right [];
extern UINT32 doodle_bitmap_left[];
extern const UINT32 monster_bitmap [];
extern const UINT32 platform_bitmap [];
extern const UINT32 broken_platform_bitmap [];
extern const UINT32 clear_bitmap[];
# 3 "renderer.c" 2
# 1 "./RENDERER.H" 1
# 1 "./MODEL.H" 1
# 41 "./RENDERER.H" 2
# 1 "./RASTER.H" 1
# 42 "./RENDERER.H" 2
# 1 "./BITMAP.H" 1
# 43 "./RENDERER.H" 2


void render(const Model *model, UINT32 *base);
void render_doodle(const Doodle *doodle, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_platform(Platform *platform, UINT32 *base);
# 4 "renderer.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 6 "renderer.c" 2


void render(Model *model, UINT32 *base)
{
    int multipleDoodleDeletions;
    render_platform(model->platforms, base);

    if(has_monster_moved(&(model->monster)) == 1)
    {
        clear_bitmap_32(base, model->monster.prev_x, model->monster.prev_y, clear_bitmap, 35 );
        render_monster(&(model->monster), base);
    }


    if(has_doodle_moved(&(model->doodle)) == 1)
    {
        clear_bitmap_32(base, model->doodle.prev_x_one, model->doodle.prev_y_one, clear_bitmap, 55 );
        if(model->doodle.prev_x_one != model->doodle.prev_x_two || model->doodle.prev_y_one != model->doodle.prev_y_two)
            clear_bitmap_32(base, model->doodle.prev_x_two, model->doodle.prev_y_two, clear_bitmap, 55 );

        if(model->doodle.prev_x_three != model->doodle.prev_x_two || model->doodle.prev_y_three != model->doodle.prev_y_two)
            clear_bitmap_32(base, model->doodle.prev_x_three, model->doodle.prev_y_three, clear_bitmap, 55 );

        render_doodle(&(model->doodle), base);

        model->doodle.prev_x_three = model->doodle.prev_x_one;
        model->doodle.prev_y_three = model->doodle.prev_y_one;
        model->doodle.prev_x_two = model->doodle.prev_x_one;
        model->doodle.prev_y_two = model->doodle.prev_y_one;
    }
}


void render_doodle(Doodle *doodle, UINT32 *base)
{
    if(doodle->facing == 1)
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_right, 55 );
    else
        plot_bitmap_32(base, doodle->x, doodle->y, doodle_bitmap_left, 55 );

}


void render_monster(Monster *monster, UINT32 *base)
{

    plot_bitmap_32(base, monster->x, monster->y, monster_bitmap, 35 );


}



void render_platform(Platform *platforms, UINT32 *base)
{
    int i;

    for(i = 0; i < 15 ; i++){
        if(has_platform_moved(platforms) == 1)
        {
            clear_bitmap_32(base, platforms->prev_x, platforms->prev_y, clear_bitmap, 22 );
            plot_bitmap_32(base, platforms->x, platforms->y, platform_bitmap, 22 );

        }
            platforms ++;
    }
}
