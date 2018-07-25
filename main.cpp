#include <cstdint>
#include <iostream>

// AM-80

struct machine {

    uint16_t rA,rB,rC,rD; //4 unsigned registers
    uint8_t sp; //stack pointer 
    uint16_t ip; //instruction pointer

    uint16_t stack[64]; 
    uint16_t system_memory[1024*1024]; 
    uint16_t program_memory[512*1024]; 

    
    uint8_t palette[256*3]; //rgb index pallete
    uint8_t video_page[320*240*4]; //4 video pages, 320x240 (modex) resolution

    uint16_t vp;  //video pointer. location to start rendering scanlines
    uint8_t vp_step; //hardware step between pixels
    uint8_t vscale;  //0 = no scaling, 255 = 16x scaling
    uint8_t vrot; // initialized to 127,= no rotation, -180 = 0, 180 = 255

    uint8_t small_sprite_page[16*16*128]; //128 tiny sprites!
    uint8_t med_sprite_page[24*24*96]; //96 medium sprites!
    uint8_t large_sprite_page[32*32*32]; //32 BIG sprites!

    // == 255 sprites

    uint8_t font_page[8*8*64]; //we'll have text
    char program_strings[1024]; //yup, this is stored seperate from system memory

    uint8_t lightness; //hardware dimming. 1 = full brightness


    // hardware video oscillators

    uint8_t vosc1_rate; //vosc1 = sin
    uint8_t vosc1_phase;
    uint8_t vosc1_a; //palette index to interpolate between on a wave
    uint8_t vosc1_b;

    uint8_t vosc2_rate //vosc2 = cos
    uint8_t vosc2_phase;
    uint8_t vosc2_a;
    uint8_t vosc2_b;

    bool osc_flag; //when enabled, colors index 0 and 1 correspond to the hardware video oscillators
    

    // hardware sprite renderer

    uint8_t sprite_x[256]; //up to 256 sprites in a pass
    uint8_t sprite_y[256];
    uint8_t sprite_rot[256]; 
    uint8_t sprite_index;  // 0-127 = tiny, (follows sprite_page layout)
    uint8_t sprite_count; //how many sprites you want to render this pass
    uint8_t sprite_effect; //the effect enabled this pass
    
    // hardware font renderer


    uint8_t font_x[16]; //up to 16 strings in a pass
    uint8_t font_y[16];
    uint16_t font_p[16]; //pointer
    uint8_t font_l[16]; //length

    // music

    /*
        p f f a n n n n

        p   = play
        ff  = effect   ( 0 = none, 1 = delay, 2 = distort, 3 = echo 
        a   = accent
        nnnn = note
    */ 

    bool music_playing;
    uint8_t sin_note[2048]; 
    uint8_t sqr_note[2048];
    uint8_t kik_note[2048];
    uint8_t snr_note[2048];
    uint8_t hat_note[2048];
    uint8_t music_effect[2048];
    uint8_t music_tempo;
    uint16_t music_length; //how long to play before looping

    // audio
    bool audio_playing;
    uint16_t pcm[1024*1024]; //pcm data
    uint16_t audio_p; //audio pointer 
    uint16_t audio_length; //how long to play before stopping

    //joystick
    uint8_t joy_x;
    uint8_t joy_y;

    bool joy_btn_a;
    bool joy_btn_b;
    bool joy_btn_x;
    bool joy_btn_y;
}
