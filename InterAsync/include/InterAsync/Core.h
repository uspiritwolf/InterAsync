#pragma once

#define BEGIN_PUBLIC_INTER_ASYNC_NAMESPACE \
	namespace ia                           \
	{
#define END_PUBLIC_INTER_ASYNC_NAMESPACE } // namespace ia

#define BEGIN_DETAILS_INTER_ASYNC_NAMESPACE \
	namespace ia::details                   \
	{
#define END_DETAILS_INTER_ASYNC_NAMESPACE } // namespace ia::details