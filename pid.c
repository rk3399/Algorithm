#include <stdio.h>
typedef struct {
    float kp;
    float ki;
    float kd;

    float err_1;

    float err_2;//上上次误差，增量式pid使用

    float err_i;//误差积分，位置式pid使用

}pid;

typedef struct
{
        float A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
        float A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
        float A2;          /**< The derived gain, A2 = Kd . */
        float state[3];    /**< The state array of length 3. */
        float Kp;          /**< The proportional gain. */
        float Ki;          /**< The integral gain. */
        float Kd;          /**< The derivative gain. */
} arm_pid_instance_f32;


float pid_start(pid *s, float setv, float cunv)
{
    float err_0 = setv - cunv;
    float pid_res = 
        s->kp * (err_0 - s->err_1) + s->ki * err_0 + s->kd * (err_0 - 2 * s->err_1 + s->err_2);


//kp * e0 - kp * e1 + ki * e0 + kd * e0 - kd * 2 * e1 + kd * e2
//kp * e0 + ki * e0 + kd * e0 - kp * e1 - kd * 2 * e1 + kd * e2
//(kp + ki + kd) * e0 - (kp + kd * 2) * e1 + kd * e2


    

    s->err_2 = s->err_1;
    s->err_1 = err_0;

    return pid_res;
}
float pid_start1(pid *s, float setv, float cunv)
{
    float err_0 = setv - cunv;
    float pid_res;
    s->err_i += err_0;

    pid_res = 
        s->kp * err_0 + s->ki * s->err_i + s->kd * (err_0 - s->err_1);

    s->err_1 = err_0;    

    return pid_res;
}

float arm_pid_f32(
  arm_pid_instance_f32 * S,
  float in)
  {
    float out;

    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

//A0 = Kp + Ki + Kd
//A1 = (-Kp ) - (2 * Kd )
//A2 = Kd  

//kp * e0 - kp * e1 + ki * e0 + kd * e0 - kd * 2 * e1 + kd * e2
//kp * e0 + ki * e0 + kd * e0 - kp * e1 - kd * 2 * e1 + kd * e2
//(kp + ki + kd) * e0 - (kp + kd * 2) * e1 + kd * e2


    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);

  }
void pid_init(pid *s)
{
    s->kp = 0.39f;
    s->ki = 0.2f;
    s->kd = 0.01f;
    s->err_1 = s->err_2 = s->err_i= 0.0;
}
void pid_init1(arm_pid_instance_f32 *s)
{
    s->Kp = s->Ki = s->Kd = 0.1f;

    s->state[0] = s->state[1] = s->state[2]= 0.0f;

        /* Derived coefficient A0 */
     s->A0 = s->Kp + s->Ki + s->Kd;

    /* Derived coefficient A1 */
     s->A1 = (-s->Kp) - ((float) 2.0f * s->Kd);

    /* Derived coefficient A2 */
    s->A2 = s->Kd;
}

float cunv = 0, retnv = 0, retnv1 = 0, retnv2 = 0;
int main1(void)
{
	
    pid s1, s2;
	
    arm_pid_instance_f32  s3;
	int delay = 0xffff;


	while(1){
        pid_init(&s1);
        pid_init(&s2);
        pid_init1(&s3);
#ifndef  __CC_ARM
        FILE *fp = fopen("res.txt", "wt");
#endif
        cunv = 0, retnv = 0, retnv1 = 0, retnv2 = 0;
		delay = 0xffff;
        for(int i = 0; i < 150;i++)
        {
            retnv = pid_start(&s1, 10, cunv);
            cunv += retnv;
		
			while(delay--);;
            retnv1 = pid_start1(&s2, 10, retnv1);
            retnv2 = arm_pid_f32(&s3, 10 - retnv2);

        #ifndef  __CC_ARM
            fprintf(fp,"%f\t%f\n",cunv, retnv1);
        #endif
           // printf("%f\r\n",cunv);
            //printf("%d:%f  %f  %f   %f\r\n",i, retnv, cunv, retnv2, retnv1);
        }
        #ifndef  __CC_ARM
           fclose(fp);
        #endif
        delay = 0xffff;while(delay--);
	}
}

