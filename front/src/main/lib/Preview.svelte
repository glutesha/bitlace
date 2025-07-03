<script lang="ts">
    import { fetchTheme } from '../theme';
    import { onMount } from 'svelte';
    import { load, remove } from '../saves';
    import { deletetool } from '../delete';
    import PreviewPixel from './PreviewPixel.svelte';

    export let display: boolean[][];
    export let id: number;

    function onClick(){
        if($deletetool){
            remove(id);
        }
        else{
            load(id);
        }
    }

    onMount(async () => {
        await fetchTheme();  
    });

</script>

<button onclick={onClick} oncontextmenu={e => e.preventDefault()} class="flex shadow-md transition duration-200 ease-in-out max-h-42.5 touch-none select-none flex-col items-center bg-black gap-1.5 p-[2px] rounded-md" 
    class:animate-jiggle={$deletetool} 
    class:shadow-red-700={$deletetool}>

{#each display as row}
    <div class="flex flex-row gap-1.5">
        {#each row as pixel}
            <PreviewPixel
                lit={pixel} 
            />
        {/each}
    </div>
{/each}
</button>