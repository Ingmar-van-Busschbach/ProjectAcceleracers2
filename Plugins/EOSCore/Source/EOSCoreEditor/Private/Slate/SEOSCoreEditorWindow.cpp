/**
* Copyright (C) 2017-2024 | eelDev AB
*/

#include "Slate/SEOSCoreEditorWindow.h"
#include "EOSCoreEditorStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

#define LOCTEXT_NAMESPACE "FEOSCoreEditorModule"

class UVersionUpdater;

void SUpdaterCoreWindow::Construct(const FArguments& InArgs)
{
	m_ModulePtr = InArgs._ModulePtr.Get();
	m_XmlData = InArgs._XmlData.Get();
	m_BrowserView = InArgs._BrowserView.Get();

	FSlateFontInfo FontTitle = FCoreStyle::Get().GetFontStyle(TEXT("NormalText"));
	FontTitle.Size = 14;

	FSlateFontInfo FontButton = FCoreStyle::Get().GetFontStyle(TEXT("NormalText"));
	FontButton.Size = 9;

	FSlateFontInfo FontButtonSmall = FCoreStyle::Get().GetFontStyle(TEXT("NormalText"));
	FontButtonSmall.Size = 7;

	FSlateFontInfo FontTiny = FCoreStyle::Get().GetFontStyle(TEXT("TinyText"));
	FontTiny.Size = 8;

	ChildSlot
	[
		SNew(SBorder)
		.Padding(0)
		.BorderImage(FEOSCoreEditorStyle::GetBrush("EOSCoreEditor.MainMenuBackground"))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					SNew(SBorder)
					.BorderImage(FEOSCoreEditorStyle::GetBrush("EOSCoreEditor.TitleBackground"))
					.Padding(8.f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(FString::Printf(TEXT("%s"), *m_XmlData.Title)))
						.Font(FontTitle)
					]
				]
				+SOverlay::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Right)
				.VAlign(EVerticalAlignment::VAlign_Center)
				.Padding(4)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(1)
					[
						SNew(SButton)
						.ButtonStyle(&FEOSCoreEditorStyle::Get().GetWidgetStyle<FButtonStyle>("EOSCoreEditor.UpdaterCoreButton")) 
						.OnClicked_Lambda([this]
						{
							FPlatformProcess::LaunchURL(*m_XmlData.Link, nullptr, nullptr);

							return FReply::Handled();
						})
						[
							SNew(STextBlock)
							.Text(FText::FromString("Read in Browser"))
							.Font(FontButton)
						]
					]
					+SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(1)
					[
						SNew(SButton)
						.ButtonStyle(&FEOSCoreEditorStyle::Get().GetWidgetStyle<FButtonStyle>("EOSCoreEditor.UpdaterCoreButton")) 
						.OnClicked_Lambda([this]
						{
							FPlatformProcess::LaunchURL(PLUGIN_LAUNCHER_URL, nullptr, nullptr);

							return FReply::Handled();
						})
						[
							SNew(STextBlock)
							.Text(FText::FromString("Epic Launcher"))
							.Font(FontButton)
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			[
				SNew(SBorder)
				.BorderImage(FEOSCoreEditorStyle::GetBrush("EOSCoreEditor.ContentBackground"))
				.Padding(0)
				[
					m_BrowserView->AsShared()
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FEOSCoreEditorStyle::GetBrush("EOSCoreEditor.ContentBackground"))
				.Padding(8.f)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(EVerticalAlignment::VAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString("This message will only appear once per update"))
						.Font(FontTiny)
					]
					+SHorizontalBox::Slot()
					.HAlign(EHorizontalAlignment::HAlign_Right)
					[
						SNew(SButton)
						.ButtonStyle(&FEOSCoreEditorStyle::Get().GetWidgetStyle<FButtonStyle>("EOSCoreEditor.UpdaterCoreButtonRed")) 
						.OnClicked_Lambda([this]
						{
							m_ModulePtr->UpdateDisableVersionCheck(true);

							TArray<TSharedRef<SWindow>> OutWindows;
							FSlateApplication::Get().GetAllVisibleWindowsOrdered(OutWindows);

							for (auto& Element : OutWindows)
							{
								if (Element->GetTitle().EqualTo(FText::FromString("Latest Plugin Update")))
								{
									FSlateApplication::Get().RequestDestroyWindow(Element);
								}
							}
							
							return FReply::Handled();
						})
						[
							SNew(STextBlock)
							.Text(FText::FromString("DISABLE UPDATES"))
							.Font(FontButtonSmall)
						]
					]
				]
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE
