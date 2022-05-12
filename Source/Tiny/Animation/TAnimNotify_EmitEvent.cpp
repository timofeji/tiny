// Fill out your copyright notice in the Description page of Project Settings.


#include "TAnimNotify_EmitEvent.h"

void UTAnimNotify_EmitEvent::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp,
	              Animation);

	// MeshComp->GetOwner()

	
}
