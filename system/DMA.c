#include "stm32f10x.h"                  // Device header
		
uint16_t MyDMA_Size;
//MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);
//MyDMA_Transfer();
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_BufferSize = Size;//�Զ���װ�� ɨ��ģʽ��ɨ��ǰ����ͨ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//������Ϊ Դ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//�������
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//�洢����ַ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;//�洢�����ݿ��
	DMA_InitStructure.DMA_MemoryInc = DMA_PeripheralInc_Enable;//�Ƿ�����
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//���ȼ�
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, DISABLE);
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);//������ϱ�־λ
}

