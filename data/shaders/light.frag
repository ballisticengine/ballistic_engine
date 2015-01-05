varying vec3 N;
varying vec3 v;    
 uniform sampler2D tex;
varying vec2 vTexCoord;    
varying in vec2 uv;
uniform int light_count;
uniform int use_light;

void main (void)  
{  
  
    if(use_light==0) {
        gl_FragColor =   texture2D(tex, gl_TexCoord[0].st); 
        return;
     }
 vec4 amb,diff,spec; 
   
for(int i=0; i<light_count; i++) {
   
float dist=distance(v, gl_LightSource[i].position.xyz)   ; 
vec3 L = normalize(gl_LightSource[i].position.xyz - v);   
   vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)  
   vec3 R = normalize(-reflect(L,N));  
 
 float atten  = 1.0 / ( dist*dist / 10000);
   //calculate Ambient Term:  
   amb += gl_FrontLightProduct[i].ambient;    

   //calculate Diffuse Term:  
    diff += gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0)*atten;    
   
   // calculate Specular Term:
   spec += gl_FrontLightProduct[i].specular  * pow(max(dot(R,E),0.0),0.3*0.00000001); 
   
    
}
// write Total Color:   //gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec +
   gl_FragColor =   diff*texture2D(tex, gl_TexCoord[0].st);   //vec4(0,0,0,0); //
}