from django.shortcuts import render, get_object_or_404
from django.views.generic import ListView
from django.core.paginator import EmptyPage, Paginator, PageNotAnInteger
from .models import Post
from .forms import EmailPostForm 

class PostListView(ListView):
    '''Alternative post list view'''
    queryset = Post.published.all()
    context_object_name = 'posts'
    paginate_by = 10
    template_name = 'blog/post/list.html'

def post_share(request, post_id):
    # Retrieve post by id 
    post = get_object_or_404( Post, id=post_id, status=Post.Status.PUBLISHED ) 
    if request.method == 'POST': # Form was submitted
        form = EmailPostForm(request.POST) 
        if form.is_valid(): # Form fields passed validation 
            cd = form.cleaned_data # ... send email 
        else: 
            form = EmailPostForm()
    return render(request, 'blog/post/share.html', {'post': post,'form': form})


def post_list(request):
    post_list = Post.published.all()
    paginator = Paginator(post_list, 1) # 1 posts in each page
    page_number = request.GET.get('page', 1)
    try: posts = paginator.page(page_number)
    except PageNotAnInteger: posts = paginator.page(1)
    except EmptyPage: posts = paginator.page(paginator.num_pages)
    return render(request, 'blog/post/list.html', {'posts': posts})

def post_detail(request, year, month, day, post): 
    post = get_object_or_404(Post, 
                             status=Post.Status.PUBLISHED, 
                             slug=post, 
                             publish__year=year, 
                             publish__month=month, 
                             publish__day=day)
    return render( request,'blog/post/detail.html', {'post': post} )
